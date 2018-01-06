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

#include "functions.hpp"
#include "parameters.hpp"

namespace model
{
    EuropeanOption::EuropeanOption(std::string typeoption, model_params::Spot spot, model_params::Strike strike, model_params::InterestRate ir, model_params::DividendYield dy, model_params::Volatility volatility, model_params::Maturity maturity)
    : m_TypeOption(typeoption), m_Spot(spot), m_Strike(strike), m_IR(ir), m_DY(dy), m_Volatility(volatility), m_Maturity(maturity)
    {
        std::cout << "Construction of European Option" << std::endl;
    }
    
    EuropeanOption::~EuropeanOption()
    {
        
    }
    
    EuropeanOption(const EuropeanOption& rhs)
    : m_TypeOption(rhs.m_TypeOption), m_Spot(rhs.m_Spot), m_Strike(rhs.m_Strike), m_IR(rhs.m_IR), m_DY(rhs.m_DY), m_Volatility(rhs.m_Volatility), m_Maturity(rhs.m_Maturity)
    {
        
    }
    
    EuropeanOption& operator=(const EuropeanOption& rhs)
    {
        m_TypeOption = rhs.m_TypeOption;
        m_Spot = rhs.m_Spot;
        m_Strike = rhs.m_Strike;
        m_IR = rhs.m_IR;
        m_DY = rhs.m_DY;
        m_Volatility = rhs.m_Volatility;
        m_Maturity = rhs.m_Maturity;
    }
    
    EuropeanOption(EuropeanOption&& rhs)
    : m_TypeOption(std::move(rhs.m_TypeOption)), m_Spot(std::move(rhs.m_Spot)), m_Strike(std::move(rhs.m_Strike)), m_IR(std::move(rhs.m_IR)), m_DY(std::move(rhs.m_DY)), m_Volatility(std::move(rhs.m_Volatility)), m_Maturity(std::move(rhs.m_Maturity))
    {
        
    }
    
    EuropeanOption& operator=(EuropeanOption&& rhs)
    {
        std::swap(m_TypeOption,rhs.m_TypeOption);
        std::swap(m_Spot,rhs.m_Spot);
        std::swap(m_Strike,rhs.m_Strike);
        std::swap(m_IR,rhs.m_IR);
        std::swap(m_DY,rhs.m_DY);
        std::swap(m_Volatility,rhs.m_Volatility);
        std::swap(m_Maturity,rhs.m_Maturity);
    }
    
    double EuropeanOption::Price()
    {
        double z = 0.0;
        if(m_TypeOption == "Call")
        {
            z = 1.0;
        }
        else
        {
            z = -1.0;
        }
        
        if m_Maturity = 0.0 return std::max(z*(m_Spot.value()-m_Strike.value()),0.0)
        
        double d1 = (std::log(m_Spot.value()/m_Strike.value()) + (m_IR.value() - m_DY.value() + 0.5*m_Volatility.value() * m_Volatility.value())*m_Maturity.value()) / (m_Volatility.value() * std::sqrt(m_Maturity.value()));
        double d2 = d1 - m_Volatility.value() * std::sqrt(m_Maturity.value());
        return z*(m_Spot.value()*std::exp(-m_DY.value()*m_Maturity.value())*func::Gaussian_Distrib_CDF(z*d1) - m_Strike.value()*std::exp(-m_IR.value()*m_Maturity.value())*func::Gaussian_Distrib_CDF(z*d2));
    }
    
    
    double EuropeanOption::Delta()
    {
        double z = 0.0;
        if(m_TypeOption == "Call")
        {
            z = 1.0;
        }
        else
        {
            z = -1.0;
        }
        
        if m_Maturity = 0.0
        {
            if std::max(z*(m_Spot.value()-m_Strike.value()),0.0) = 0 return 0;
            else return z
        }
        
        double d1 = (std::log(m_Spot.value()/m_Strike.value()) + (m_IR.value() - m_DY.value() + 0.5*m_Volatility.value()*m_Volatility.value())*m_Maturity.value()) / (m_Volatility.value() * std::sqrt(m_Maturity.value()));
        return z*func::Gaussian_Distrib_CDF(z*d1);
    }
    
    double EuropeanOption::UnderlyingH()
    {
        return Delta() * m_Spot.value();
    }
    
    
    double EuropeanOption::Cash()
    {
        return Price() - UnderlyingH();
    }
    
    
}
