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
    model_params::Strike strike(2000.0);
    model_params::Volatility vol(0.2);
    model_params::Maturity mat(1.);
    
    model::EuropeanOption option("Call", spot, strike, ir, dy, vol, mat);
    std::cout << "Price: " << option.Price() << std::endl;
    std::cout << "Delta: " << option.Delta() << std::endl;
    
    std::vector<double> Spots(5,0.0);
    std::vector<double> Prices(5,0.0);
    std::vector<double> Deltas(5,0.0);
    std::vector<double> Cash(5,0.0);


    Spots[0] = 2500.0;
    Spots[1] = 2450.0;
    Spots[2] = 2550.0;
    Spots[3] = 2300.0;
    Spots[4] = 2400.0;
    
    std::size_t LengthVector = Spots.size();
    
    for(std::size_t i = 0;i<LengthVector;++i)
    {
        model::EuropeanOption option2("Call", Spots[i], strike, ir, dy, vol, mat);
        Prices[i] = option2.Price();
        Deltas[i] = option2.Delta();
        Cash[i] = option2.Cash();
    }
}

int main(int argc, char* argv[])
{
    test_param();
    return 0;
}
