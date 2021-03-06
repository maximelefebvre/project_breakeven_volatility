#include "functions.hpp"

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
    double erf(double x)
    {
        double y = 1.0 / ( 1.0 + 0.3275911 * x);
        return 1 - (((((
                        + 1.061405429  * y
                        - 1.453152027) * y
                       + 1.421413741) * y
                      - 0.284496736) * y
                     + 0.254829592) * y)
        * std::exp (-x * x);
    }
    
    // Returns the probability of x, given the distribution described by mu and sigma.
    double Gaussian_Distrib_PDF(double x, double mu, double sigma)
    {
        //Constants
        static const double pi = 3.14159265;
        return std::exp( -1 * (x - mu) * (x - mu) / (2 * sigma * sigma)) / (sigma * std::sqrt(2 * pi));
    }
    
    // Returns the probability of [-inf,x] of a gaussian distribution
    double Gaussian_Distrib_CDF(double x, double mu, double sigma)
    {
        return 0.5 * (1 + erf((x - mu) / (sigma * std::sqrt(2.))));
    }
    
    double BlackScholes_Price(double Spot, double Strike, double Volatility, double IR, double DY, double Maturity,bool Call)
    {
        double d1 = (std::log(Spot/Strike) + (IR - DY + 0.5*Volatility*Volatility)*Maturity) / (Volatility * std::sqrt(Maturity));
        double d2 = d1 - Volatility * std::sqrt(Maturity);
        double z=0.0;
        if(Call == true)
        {
            z=1.0;
        }
        else
        {
            z=-1.0;
        }
        return z*(Spot*std::exp(-DY*Maturity)*Gaussian_Distrib_CDF(z*d1) - Strike*std::exp(-IR*Maturity)*Gaussian_Distrib_CDF(z*d2));
    }
    
    double BlackScholes_Delta(double Spot, double Strike, double Volatility, double IR, double DY, double Maturity,bool Call)
    {
        double d1 = (std::log(Spot/Strike) + (IR - DY + 0.5*Volatility*Volatility)*Maturity) / (Volatility * std::sqrt(Maturity));
        double d2 = d1 - Volatility * std::sqrt(Maturity);
        
        double z=0.0;
        if(Call == true)
        {
            z=1.0;
        }
        else
        {
            z=-1.0;
        }
        return z*Gaussian_Distrib_CDF(z*d1);
    }
    
    double BlackScholes_Gamma(double Spot, double Strike, double Volatility, double IR, double DY, double Maturity)
    // No need to specify "Call" or "Put" since Gamma is equal for either
    {
        double d1=(std::log(Spot/Strike)+(IR-DY+0.5*Volatility*Volatility)*Maturity)/(Volatility*std::sqrt(Maturity));
        
        return std::exp(-DY*Maturity)*Gaussian_Distrib_PDF(d1)/(Spot*Volatility*std::sqrt(Maturity));
    }
}
