#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "functions.hpp"
#include "import_data.hpp"
#include "parameters.hpp"
#include "pricing_hedging.hpp"

void test_param()
{
    model_params::InterestRate ir(0.1);
    model_params::DividendYield dy(0.02);
    model_params::Spot spot(100.0);
    model_params::Strike strike(80.0);
    model_params::Volatility vol(0.2);
    model_params::Maturity mat(1.);
    
    model::EuropeanOption option("Call", spot, strike, ir, dy, vol, mat);
    std::cout << "Price: " << option.Price() << std::endl;
    std::cout << "Delta: " << option.Delta() << std::endl;
}

int main(int argc, char* argv[])
{
    test_param();
    return 0;
}
