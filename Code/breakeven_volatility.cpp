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
        std::size_t NbDays = Spots.size();
        //NbDays = EndDate - StartDate;
        
        model_params::Spot spot(Spots[0]);
        model_params::Maturity mat(double(NbDays)/365.0);
        
        std::vector<double> Prices;
        std::vector<double> Delta;
        std::vector<double> SpotPositions;
        std::vector<double> CashPositions;
        std::vector<double> PnLVector;
        
        model::EuropeanOption option("Call", spot, strikeprice, ir, dy, vol, mat);
        Prices.push_back(option.Price());
        Delta.push_back(option.Delta());
        SpotPositions.push_back(option.UnderlyingH());
        CashPositions.push_back(option.Cash());
        PnLVector.push_back(0.0);
        
        for(std::size_t i = 1;i<NbDays+1;++i)
        {
            std::size_t NbDaysLeft;
            NbDaysLeft = NbDays - i;
            // NbDaysLeft = EndDate - StartDate - i;
            model_params::Maturity mat(double(NbDaysLeft)/365.0);
            model_params::Spot spot(Spots[i]);
            model::EuropeanOption option("Call", spot, strikeprice, ir, dy, vol, mat);
            Prices.push_back(option.Price());
            Delta.push_back(option.Delta());
            SpotPositions.push_back(option.UnderlyingH());
            CashPositions.push_back(option.Cash());
            PnLVector.push_back((Prices[i] - Prices[i-1]) - Delta[i-1]*(Spots[i]-Spots[i-1]) - std::exp(ir.value()/365.0)*CashPositions[i-1]);
        }
        /*std::cout << "Pnl vector : (";
        for (std::vector<double>::const_iterator i = PnLVector.begin(); i != PnLVector.end(); ++i)
        {
            std::cout << *i << ',';
        }
        std::cout << ")" << std::endl << std::endl;*/
        
        double PnL = std::accumulate(PnLVector.begin(), PnLVector.end(), 0);
        //std::cout << PnL << std::endl;
        return PnL;
    }
    
    model_params::Volatility FindVolatility(const model_params::Strike strikeprice, const date StartDate, const date EndDate, const std::vector<double> Spots, const model_params::InterestRate ir, const model_params::DividendYield dy)
    {
        double LowerBound = 0.;
        double UpperBound = 20.;
        model_params::Volatility vol((LowerBound+UpperBound)/2);
        //std::cout << ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots, ir, dy) << std::endl;
        while(std::abs(ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots,ir,dy)) > std::pow(10,-1))
        {
            //std::cout << ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots, ir, dy) << std::endl;
            if(ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots, ir, dy) > 0)
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
        model_params::Volatility vol(0.0); // initial value for the vector
        std::vector<model_params::Volatility> VolatilitySmile;
        
        for(std::size_t i = 0;i<Strikes.size();++i)
        {
            model_params::Strike strike(Strikes[i]);
            model_params::Volatility vol = FindVolatility(strike,date(2016,06,30),date(2017,06,29),Spots,ir,dy);
            VolatilitySmile.push_back(vol);
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
