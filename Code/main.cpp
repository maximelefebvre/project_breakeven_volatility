#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "functions.hpp"
#include "import_data.hpp"
#include "parameters.hpp"
#include "pricing_hedging.hpp"

double ValueOfPnL(const double volatility, const double strikeprice, const double maturity, const std::vector<double> Spots)
{
    std::size_t LengthVector = Spots.size();
    
    model_params::InterestRate ir(0.1);
    model_params::DividendYield dy(0.02);
    model_params::Spot spot(100.0);
    model_params::Strike strike(strikeprice);
    model_params::Volatility vol(volatility);
    model_params::Maturity mat(maturity);
    
    model::EuropeanOption option("Call", spot, strike, ir, dy, vol, mat);
    std::cout << "Price: " << option.Price() << std::endl;
    std::cout << "Delta: " << option.Delta() << std::endl;
    
    std::vector<double> Prices(LengthVector,0.0);
    std::vector<double> Delta(LengthVector,0.0);
    std::vector<double> SpotPositions(LengthVector,0.0);
    std::vector<double> CashPositions(LengthVector,0.0);
    std::vector<double> PnLVector(LengthVector,0.0);
    
    for(std::size_t i = 0;i<LengthVector;++i)
    {
        model_params::Maturity mat2(1.0-i/LengthVector);
        model::EuropeanOption option2("Call", Spots[i], strike, ir, dy, vol, mat2);
        Prices[i] = option2.Price();
        Delta[i] = option2.Delta();
        SpotPositions[i] = option2.UnderlyingH();
        CashPositions[i] = option2.Cash();
        
        if(i > 0)
        {
            PnLVector[i] = (Prices[i] - Prices[i-1]) - Delta[i-1]*(Spots[i]-Spots[i-1]) - std::exp(ir.value() * 1/LengthVector)*CashPositions[i-1];
        }
    }
    double PnL = std::accumulate(PnLVector.begin(), PnLVector.end(), 0);
    return PnL;
}

double FindVolatility(const double strikeprice, const double maturity, const std::vector<double> Spots)
{
    double LowerBound = 0.;
    double UpperBound = 1000.;
    double temp = (LowerBound+UpperBound)/2;
    while(std::abs(ValueOfPnL(temp,strikeprice,maturity,Spots)) > std::pow(10,-3))
    {
        if(ValueOfPnL(temp,strikeprice,maturity,Spots) >= 0)
        {
            LowerBound = temp;
        }
        else
        {
            UpperBound = temp;
        }
        temp = (LowerBound+UpperBound)/2;
    }
    return temp;
}

void BreakEvenVolatility()
{
    std::vector<double> Spots(5,0.0);
    Spots[0] = 2500.0;
    Spots[1] = 2450.0;
    Spots[2] = 2550.0;
    Spots[3] = 2300.0;
    Spots[4] = 2400.0;
    
    std::vector<double> Strikes({2000.0,2100.0,2200.0,2300.0,2400.0,2500.0});
    std::vector<double> VolatilitySmile(Strikes.size(),0.);
    
    for(std::size_t i = 0;i<Strikes.size();++i)
    {
        double vol = FindVolatility(Strikes[i],1.0,Spots);
        std::cout << vol << std::endl;
        VolatilitySmile[i] = vol;
    }
    
    std::cout << "Volatility Smile : (";
    for(std::size_t i = 0;i<Strikes.size();++i)
    {
        std::cout << VolatilitySmile[i] << ",";
    }
    std::cout << ")" << std::endl;
}

typedef std::vector <double> record_t;
typedef std::vector <record_t> data_t;

//-----------------------------------------------------------------------------
// Let's overload the stream input operator to read a list of CSV fields (which a CSV record).
// Remember, a record is a list of doubles separated by commas ','.
std::istream& operator >> ( std::istream& ins, record_t& record )
{
    // make sure that the returned record contains only the stuff we read now
    record.clear();
    
    // read the entire line into a string (a CSV record is terminated by a newline)
    std::string line;
    getline( ins, line );
    
    // now we'll use a stringstream to separate the fields out of the line
    std::stringstream ss( line );
    std::string field;
    while (getline( ss, field, ',' ))
    {
        // for each field we wish to convert it to a double
        // (since we require that the CSV contains nothing but floating-point values)
        std::stringstream fs( field );
        double f = 0.0;  // (default value is 0.0)
        fs >> f;
        
        // add the newly-converted field to the end of the record
        record.push_back( f );
    }
    
    // Now we have read a single line, converted into a list of fields, converted the fields
    // from strings to doubles, and stored the results in the argument record, so
    // we just return the argument stream as required for this kind of input overload function.
    return ins;
}

//-----------------------------------------------------------------------------
// Let's likewise overload the stream input operator to read a list of CSV records.
// This time it is a little easier, just because we only need to worry about reading
// records, and not fields.
std::istream& operator >> ( std::istream& ins, data_t& data )
{
    // make sure that the returned data only contains the CSV data we read here
    data.clear();
    
    // For every record we can read from the file, append it to our resulting data
    record_t record;
    while (ins >> record)
    {
        data.push_back( record );
    }
    
    // Again, return the argument stream as required for this kind of input stream overload.
    return ins;
}

data_t get_data(std::string NameOfTheFile)
{
    // Here is the data we want.
    data_t data;
    
    // Here is the file containing the data. Read it into data.
    std::ifstream infile( NameOfTheFile );
    infile >> data;
    
    // Complain if something went wrong.
    /*if (!infile.eof())
    {
        throw std::runtime_error("Problem with your data");
    }*/
    
    infile.close();
    
    // Otherwise, list some basic information about the file.
    std::cout << "Your CSV file contains " << data.size() << " records.\n";
    
    std::size_t max_record_size = 0;
    for (std::size_t i = 0; i < data.size(); ++i)
        if (max_record_size < data[i].size())
        {
            max_record_size = data[i].size();
        }
    std::cout << "The largest record has " << max_record_size << " fields.\n";
    
    std::cout << "The second field in the fourth record contains the value " << data[ 3 ][ 1 ] << ".\n";
    
    std::cout << "Good bye!\n";
    
    return data;
}




int main(int argc, char* argv[])
{
    std::string name("SPX500.csv");
    data_t Prices = get_data(name);
    std::ifstream infile(name);
    //std::string str;
    //infile >> str;
    //std::cout << str << std::endl;
    
    
    
    /*std::vector<double> Spots(5,0.0);
    Spots[0] = 2500.0;
    Spots[1] = 2450.0;
    Spots[2] = 2550.0;
    Spots[3] = 2300.0;
    Spots[4] = 2400.0;

    std::size_t LengthVector = Spots.size();
    
    model_params::InterestRate ir(0.1);
    model_params::DividendYield dy(0.02);
    model_params::Spot spot(2000.0);
    model_params::Strike strike(2400.0);
    model_params::Volatility vol(4.);
    model_params::Maturity mat(1.);
    
    model::EuropeanOption option("Call", spot, strike, ir, dy, vol, mat);
    std::cout << "Price: " << option.Price() << std::endl;
    std::cout << "Delta: " << option.Delta() << std::endl;
    
    std::vector<double> Prices(LengthVector,0.0);
    std::vector<double> Delta(LengthVector,0.0);
    std::vector<double> SpotPositions(LengthVector,0.0);
    std::vector<double> CashPositions(LengthVector,0.0);
    std::vector<double> PnLVector(LengthVector,0.0);
    
    for(std::size_t i = 0;i<LengthVector;++i)
    {
        model_params::Maturity mat2(1.0-i/LengthVector);
        model::EuropeanOption option2("Call", Spots[i], strike, ir, dy, vol, mat2);
        Prices[i] = option2.Price();
        Delta[i] = option2.Delta();
        SpotPositions[i] = option2.UnderlyingH();
        CashPositions[i] = option2.Cash();
        
        if(i > 0)
        {
            PnLVector[i] = (Prices[i] - Prices[i-1]) - Delta[i-1]*(Spots[i]-Spots[i-1]) - std::exp(ir.value() *1/LengthVector)*CashPositions[i-1];
        }
    }
    double PnL = std::accumulate(PnLVector.begin(), PnLVector.end(), 0);
    
    std::cout << PnL << std::endl;*/
    return 0;
}
