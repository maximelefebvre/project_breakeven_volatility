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
#include "import_data.hpp"
#include "parameters.hpp"
#include "pricing_hedging.hpp"
#include "dates.hpp"
#include "breakeven_volatility.hpp"


int main(int argc, char* argv[])
{
    std::string name("SPX500.csv");
    data_importation::data_t Prices = data_importation::get_data(name);
    std::cout << Prices[8][100] << std::endl;
    
    std::vector<double> Spots(5,0.0);
    Spots[0] = 2500.0;
    Spots[1] = 2450.0;
    Spots[2] = 2550.0;
    Spots[3] = 2300.0;
    Spots[4] = 2400.0;
    
    //Declare a vector of Strikes
    double initialstrike = 1500.;
    std::vector<double> Strikes(2000);
    std::iota(Strikes.begin(),Strikes.end(),initialstrike);
    
    //Declare Interest Rate and Dividend Yield
    model_params::InterestRate ir(0.1);
    model_params::DividendYield dy(0.02);
    
    //Compute Volatility Smile
    std::vector<model_params::Volatility> VolatilitySmile = BEV::BreakEvenVolatility(Spots, Strikes, ir,dy);
    return 0;
}
