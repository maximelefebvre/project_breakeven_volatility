#include "breakeven_volatility.hpp"

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
#include "parameters.hpp"
#include "pricing_hedging.hpp"
#include "dates.hpp"

namespace BEV
{
    double ValueOfPnL(const model_params::Volatility vol, const model_params::Strike strikeprice, const date StartDate, const date EndDate, const std::vector<double> Spots, const model_params::InterestRate ir, const model_params::DividendYield dy)
    {
        int NbDays;
        NbDays = EndDate - StartDate;
        
        model_params::Spot spot(Spots[0]);
        model_params::Maturity mat(double(NbDays)/365.0);
        
        std::vector<double> Prices(NbDays+1,0.0);
        std::vector<double> Delta(NbDays+1,0.0);
        std::vector<double> SpotPositions(NbDays+1,0.0);
        std::vector<double> CashPositions(NbDays+1,0.0);
        std::vector<double> PnLVector(NbDays+1,0.0);
        
        model::EuropeanOption option("Call", spot, strikeprice, ir, dy, vol, mat);
        Prices[0] = option.Price();
        Delta[0] = option.Delta();
        std::cout << "Price: " << option.Price() << std::endl;
        std::cout << "Delta: " << option.Delta() << std::endl;
        SpotPositions[0]=option.UnderlyingH();
        CashPositions[0]=option.Cash();
        PnLVector[0]=0.0;
        
        for(std::size_t i = 1;i<NbDays+1;++i)
        {
            int NbDaysLeft;
            NbDaysLeft = EndDate - StartDate - i;
            model_params::Maturity mat(double(NbDaysLeft)/365.0);
            model::EuropeanOption option("Call", Spots[i], strikeprice, ir, dy, vol, mat);
            Prices[i] = option.Price();
            Delta[i] = option.Delta();
            SpotPositions[i] = option.UnderlyingH();
            CashPositions[i] = option.Cash();
            PnLVector[i] = (Prices[i] - Prices[i-1]) - Delta[i-1]*(Spots[i]-Spots[i-1]) - std::exp(ir.value()/365.0)*CashPositions[i-1];
        }
        double PnL = std::accumulate(PnLVector.begin(), PnLVector.end(), 0);
        return PnL;
    }
    
    model_params::Volatility FindVolatility(const model_params::Strike strikeprice, const date StartDate, const date EndDate, const std::vector<double> Spots, const model_params::InterestRate ir, const model_params::DividendYield dy)
    {
        double LowerBound = 0.;
        double UpperBound = 1000.;
        model_params::Volatility vol((LowerBound+UpperBound)/2);
        while(std::abs(ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots,ir,dy)) > std::pow(10,-3))
        {
            if(ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots, ir, dy) >= 0)
            {
                LowerBound = vol.value();
            }
            else
            {
                UpperBound = vol.value();
            }
            model_params::Volatility vol((LowerBound+UpperBound)/2);
        }
        return vol;
    }
    
    std::vector<model_params::Volatility> BreakEvenVolatility(const std::vector<double> Spots, const std::vector<double> Strikes, const model_params::InterestRate ir, const model_params::DividendYield dy)
    {
        std::vector<model_params::Volatility> VolatilitySmile(Strikes.size(),0.);
        
        for(std::size_t i = 0;i<Strikes.size();++i)
        {
            model_params::Strike strike(Strikes[i]);
            model_params::Volatility vol = FindVolatility(strike,date(2016,06,30),date(2017,06,30),Spots,ir,dy);
            std::cout << vol.value() << std::endl;
            VolatilitySmile[i] = vol;
        }
        
        std::cout << "Volatility Smile : (";
        for(std::size_t i = 0;i<Strikes.size();++i)
        {
            std::cout << VolatilitySmile[i].value();
            if(i < Strikes.size()-1)
            {
                std::cout << ",";
            }
        }
        std::cout << ")" << std::endl;
        
        return VolatilitySmile;
    }
}
