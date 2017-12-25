#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "functions.hpp"
#include "parameters.hpp"
#include "pricing_hedging.hpp"


int main(int argc, char* argv[])
{
    double x = 0.5;
    double mu = 0.;
    double sigma = 1.;
    double result = func::Gaussian_Distrib_CDF(x,mu,sigma);
    
    std::cout << "Gaussian RV probability <=: " << x << " is: " << result;
    return 0;
}
