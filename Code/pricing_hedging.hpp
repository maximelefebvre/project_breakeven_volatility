#ifndef PRICING_HEDGING_HPP
#define PRICING_HEDGING_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "parameters.hpp"

namespace model
{
    
    class EuropeanOption
    {
    public:
        EuropeanOption(std::string typeoption, model_params::Spot spot, model_params::Strike strike, model_params::InterestRate ir, model_params::DividendYield dy, model_params::Volatility volatility, model_params::Maturity maturity);
        ~EuropeanOption();
        double Price();
        double Delta();
        double UnderlyingH();
        double Cash();
    protected:
    private:
        std::string m_TypeOption;
        model_params::Spot m_Spot;
        model_params::Strike m_Strike;
        model_params::InterestRate m_IR;
        model_params::DividendYield m_DY;
        model_params::Volatility m_Volatility;
        model_params::Maturity m_Maturity;

    };
}

#endif
