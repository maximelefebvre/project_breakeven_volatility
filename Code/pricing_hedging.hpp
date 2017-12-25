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
    enum class TypeOption
    {
        Call,
        Put
    };
    
    class EuropeanOption
    {
    public:
        EuropeanOption(TypeOption typeoption, Spot* spot, Strikes* strikes, InterestRate* ir, DividendYield* dy, Volatility* volatility, Maturity* maturity);
    protected:
    private:
        TypeOption m_TypeOption;
        model_params::Spot* p_Spot;
        model_params::Strikes* p_Strikes;
        model_params::InterestRate* p_IR;
        model_params::DividendYield* p_DY;
        model_params::Volatility* p_Volatility;
        model_params::Maturity* p_Maturity;

    };
}

#endif
