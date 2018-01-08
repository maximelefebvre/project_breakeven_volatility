#ifndef BREAKEVEN_VOLATILITY_HPP
#define BREAKEVEN_VOLATILITY_HPP

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
    const double ValueOfPnL(const model_params::Volatility vol, const model_params::Strike strikeprice, const std::date StartDate, const std::date EndDate, const std::vector<double> Spots, const model_params::InterestRate ir, const model_params::DividendYield dy, const std::string TypeOption);
    const double ValueOfPnL_BlackScholesRobustnessFormula(const model_params::Volatility vol, const model_params::Strike strikeprice, const std::date StartDate, const std::date EndDate, const std::vector<double> Spots, const model_params::InterestRate ir, const model_params::DividendYield dy, const std::string TypeOption);
    const model_params::Volatility FindVolatility(const model_params::Strike strikeprice, const std::date StartDate, const std::date EndDate, const std::vector<double> Spots, const model_params::InterestRate ir, const model_params::DividendYield dy, const std::string TypeOption, const std::string method);
    const std::vector<model_params::Volatility> BreakEvenVolatility(const std::vector<double> Spots, const std::vector<double> Strikes, const model_params::InterestRate ir, const model_params::DividendYield dy, const std::string TypeOption, const std::string method);
}

#endif
