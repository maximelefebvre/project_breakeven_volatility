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
    double ValueOfPnL(const model_params::Volatility vol, const model_params::Strike strikeprice, const date StartDate, const date EndDate, const std::vector<double> Spots, const model_params::InterestRate ir, const model_params::DividendYield dy, const std::string TypeOption)
    {
        std::size_t NbDays = Spots.size();
        /*int k = EndDate - StartDate;
         std::size_t NbDays = size_t(k);*/
        
        model_params::Spot spot(Spots[0]);
        model_params::Maturity mat(double(NbDays)/252.0);
        
        std::vector<double> Prices;
        std::vector<double> Delta;
        std::vector<double> SpotPositions;
        std::vector<double> CashPositions;
        std::vector<double> PnLVector;
        
        model::EuropeanOption option(TypeOption, spot, strikeprice, ir, dy, vol, mat);
        Prices.push_back(option.Price());
        Delta.push_back(option.Delta());
        SpotPositions.push_back(option.UnderlyingH());
        CashPositions.push_back(option.Cash());
        PnLVector.push_back(Prices[0]);
        
        for(std::size_t i = 1;i<NbDays-1;++i)
        {
            std::size_t NbDaysLeft;
            NbDaysLeft = NbDays - i;
            // NbDaysLeft = EndDate - StartDate - i;
            model_params::Maturity mat(double(NbDaysLeft)/252.0);
            model_params::Spot spot(Spots[i]);
            model::EuropeanOption option(TypeOption, spot, strikeprice, ir, dy, vol, mat);
            Prices.push_back(option.Price());
            Delta.push_back(option.Delta());
            SpotPositions.push_back(option.UnderlyingH());
            CashPositions.push_back(option.Cash());
            double CurrentPnL = std::accumulate(PnLVector.begin(), PnLVector.end(), 0);
            PnLVector.push_back(Delta[i-1]*(Spots[i]-Spots[i-1]) + (std::exp(ir.value()/252.0)-1)*(CurrentPnL-SpotPositions[i]));
        }
        if(TypeOption == "Call")
        {
            PnLVector.push_back(-1.*std::max(Spots[Spots.size()-1]-strikeprice.value(),0.));
        }
        else
        {
            PnLVector.push_back(-1.*std::max(strikeprice.value()-Spots[Spots.size()-1],0.));
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
    
    model_params::Volatility FindVolatility(const model_params::Strike strikeprice, const date StartDate, const date EndDate, const std::vector<double> Spots, const model_params::InterestRate ir, const model_params::DividendYield dy, const std::string TypeOption)
    {
        double LowerBound = 0.;
        double UpperBound = 50.; // Large upper bound in order to make sure the solution is in the interval, otherwise it would diverge
        model_params::Volatility vol((LowerBound+UpperBound)/2);
        //std::cout << ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots, ir, dy,TypeOption) << std::endl;
        while(std::abs(ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots,ir,dy,TypeOption)) > std::pow(10,-3))
        {
            //std::cout << ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots, ir, dy,TypeOption) << std::endl;
            if(ValueOfPnL(vol,strikeprice,StartDate, EndDate, Spots, ir, dy,TypeOption) > 0)
            {
                UpperBound = vol.value();
            }
            else
            {
                LowerBound = vol.value();
            }
            model_params::Volatility vol((LowerBound+UpperBound)/2);
        }
        return vol;
    }
    
    std::vector<model_params::Volatility> BreakEvenVolatility(const std::vector<double> Spots, const std::vector<double> Strikes, const model_params::InterestRate ir, const model_params::DividendYield dy, const std::string TypeOption)
    {
        model_params::Volatility vol(0.0); // initial value for the vector
        std::vector<model_params::Volatility> VolatilitySmile;
        
        for(std::size_t i = 0;i<Strikes.size();++i)
        {
            model_params::Strike strike(Strikes[i]);
            model_params::Volatility vol = FindVolatility(strike,date(2016,06,30),date(2017,06,29),Spots,ir,dy,TypeOption);
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
