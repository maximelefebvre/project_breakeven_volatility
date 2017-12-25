#include "pricing_hedging.hpp"
#include "parameters.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>


namespace model
{
    EuropeanOption::EuropeanOption(TypeOption typeoption, Spot* spot, Strikes* strikes, InterestRate* ir, DividendYield* dy, Volatility* volatility, Maturity* maturity)
    : m_TypeOption(typeoption), 
    {
        std::cout << "Construction of European Option" << std::endl;
    }
}
