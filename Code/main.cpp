#include <algorithm>
#include <array>
#include <cmath>
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
        model_params::Maturity mat2(maturity*(1.0-i/LengthVector));
        model::EuropeanOption option2("Call", Spots[i], strike, ir, dy, vol, mat2);
        Prices[i] = option2.Price();
        Delta[i] = option2.Delta();
        SpotPositions[i] = option2.UnderlyingH();
        CashPositions[i] = option2.Cash();
        
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
    double UpperBound = 50.;
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

int main(int argc, char* argv[])
{
    std::vector<double> Spots(5,0.0);
    Spots[0] = 2500.0;
    Spots[1] = 2450.0;
    Spots[2] = 2550.0;
    Spots[3] = 2300.0;
    Spots[4] = 2400.0;
    
    std::vector<double> Strikes({2000.0,2100.0,2200.0,2300.0,2400.0,2500.0});
    //std::vector<double> VolatilitySmile(Strikes.size(),0.);
    
    for(std::size_t i = 0;i<Strikes.size();++i)
    {
        double vol = FindVolatility(Strikes[i],1.0,Spots);
        std::cout << vol << std::endl;
        //VolatilitySmile[i] = vol;
    }
    
    /*std::cout << "Volatility Smile : (";
    for(std::size_t i = 0;i<Strikes.size();++i)
    {
        std::cout << VolatilitySmile[i] << ",";
    }
    std::cout << ")" << std::endl; */
    return 0;
}
