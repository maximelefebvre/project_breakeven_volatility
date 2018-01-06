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
#include "dates.hpp"

//double ValueOfPnL(const double volatility, const double strikeprice, const double maturity, const std::vector<double> Spots)
double ValueOfPnL(const double volatility, const double strikeprice, const date StartDate, const date EndDate, const std::vector<double> Spots)
{
    //std::size_t LengthVector = Spots.size();
    NbDays = EndDate - StartDate;
    
    model_params::InterestRate ir(0.1);
    model_params::DividendYield dy(0.02);
    //model_params::Spot spot(100.0);
    model_params::Spot spot(Spots[0]);
    model_params::Strike strike(strikeprice);
    model_params::Volatility vol(volatility);
    //model_params::Maturity mat(maturity);
    model_params::Maturity mat(double(NbDays)/365.0);
    
    /*std::vector<double> Prices(LengthVector,0.0);
    std::vector<double> Delta(LengthVector,0.0);
    std::vector<double> SpotPositions(LengthVector,0.0);
    std::vector<double> CashPositions(LengthVector,0.0);
    std::vector<double> PnLVector(LengthVector,0.0);*/
    
    std::vector<double> Prices(NbDays+1,0.0);
    std::vector<double> Delta(NbDays+1,0.0);
    std::vector<double> SpotPositions(NbDays+1,0.0);
    std::vector<double> CashPositions(NbDays+1,0.0);
    std::vector<double> PnLVector(NbDays+1,0.0);
    
    model::EuropeanOption option("Call", spot, strike, ir, dy, vol, mat);
    Prices[0] = option.Price();
    Delta[0] = option.Delta();
    std::cout << "Price: " << option.Price() << std::endl;
    std::cout << "Delta: " << option.Delta() << std::endl;
    SpotPositions[0]=option.UnderlyingH();
    CashPositions[0]=option.Cash();
    PnLVector[0]=0.0
    
    for(std::size_t i = 1;i<NbDays+1;++i)
    {
        NbDaysLeft = EndDate - StartDate + i
        /*model_params::Maturity mat2(double(NbDaysLeft)/365.0);
        model::EuropeanOption option2("Call", Spots[i], strike, ir, dy, vol, mat2);
        Prices[i] = option2.Price();
        Delta[i] = option2.Delta();
        SpotPositions[i] = option2.UnderlyingH();
        CashPositions[i] = option2.Cash();*/
        model_params::Maturity mat(double(NbDaysLeft)/365.0);
        model::EuropeanOption option("Call", Spots[i], strike, ir, dy, vol, mat);
        Prices[i] = option.Price();
        Delta[i] = option.Delta();
        SpotPositions[i] = option.UnderlyingH();
        CashPositions[i] = option.Cash();
        PnLVector[i] = (Prices[i] - Prices[i-1]) - Delta[i-1]*(Spots[i]-Spots[i-1]) - std::exp(ir.value() *maturity/LengthVector)*CashPositions[i-1];
        if(i > 0)
        {
            PnLVector[i] = (Prices[i] - Prices[i-1]) - Delta[i-1]*(Spots[i]-Spots[i-1]) - std::exp(ir.value() *maturity/LengthVector)*CashPositions[i-1];
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
    while(std::abs(ValueOfPnL(temp/100,strikeprice,maturity,Spots)) > std::pow(10,-3))
    {
        if(ValueOfPnL(temp/100,strikeprice,maturity,Spots) >= 0)
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





int main(int argc, char* argv[])
{
    std::string name("SPX500.csv");
    data_importation::data_t Prices = data_importation::get_data(name);
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
