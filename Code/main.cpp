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
    std::string name("../SPX500-python_transformed.csv");
    data_importation::data_t Prices = data_importation::get_data(name);
    std::size_t column_to_keep = 4;
    std::vector<double> Spots = data_importation::transform_datastructure(Prices,column_to_keep);
    
    std::cout << std::endl;
    std::cout << "Spots vector : (";
    for (std::vector<double>::const_iterator i = Spots.begin(); i != Spots.end(); ++i)
    {
        std::cout << *i << ',';
    }
    std::cout << ")" << std::endl << std::endl;

    
    //Declare a vector of Strikes
    std::vector<double> Strikes({2000.0,2200.0,2400.0});
    
    // If you have a powerful computer, try this vector of strikes:
    //double initialstrike = 1500.;
    //std::vector<double> Strikes(2000);
    //std::iota(Strikes.begin(),Strikes.end(),initialstrike);
    std::cout << "Strikes vector : (";
    for (std::vector<double>::const_iterator i = Strikes.begin(); i != Strikes.end(); ++i)
    {
        std::cout << *i << ',';
    }
    std::cout << ")" << std::endl << std::endl;
    
    //Declare Interest Rate and Dividend Yield
    model_params::InterestRate ir(0.1);
    model_params::DividendYield dy(0.02);
    
    //Compute Volatility Smile
    std::vector<model_params::Volatility> VolatilitySmile = BEV::BreakEvenVolatility(Spots, Strikes, ir,dy);
    return 0;
}
