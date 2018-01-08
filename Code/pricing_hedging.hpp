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
        EuropeanOption(const std::string typeoption, const model_params::Spot spot, const model_params::Strike strike, const model_params::InterestRate ir, const model_params::DividendYield dy, const model_params::Volatility volatility, const model_params::Maturity maturity);
        ~EuropeanOption();
        EuropeanOption(const EuropeanOption& rhs);
        EuropeanOption& operator=(const EuropeanOption& rhs);
        EuropeanOption(EuropeanOption&& rhs);
        EuropeanOption& operator=(EuropeanOption&& rhs);
        
        double Price();
        double Delta();
        double UnderlyingH();
        double Cash();
        double Gamma();
        double GammaCash();
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
