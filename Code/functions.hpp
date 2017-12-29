#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace func
{
    double erf(double x);
    double Gaussian_Distrib_PDF(double x, double mu = 0, double sigma = 1);
    double Gaussian_Distrib_CDF(double x, double mu = 0, double sigma = 1);
    double BlackScholes_Price(double Spot, double Strike, double Volatility, double IR, double DY, double Maturity,bool Call = true);
    double BlackScholes_Delta(double Spot, double Strike, double Volatility, double IR, double DY, double Maturity,bool Call = true);
    double BlackScholes_Gamma(double Spot, double Strike, double Volatility, double IR, double DY, double Maturity);
}

#endif

