#include "parameters.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace model_params
{
    //////////////////////////////////////////////////////
    /////////////// CLASS INTEREST RATE
    //////////////////////////////////////////////////////
    
    InterestRate::InterestRate(const double IR)
    : m_IR_value(IR)
    {
        std::cout << "Use Constructor of Interest Rate" << std::endl;
    }
    
    InterestRate::~InterestRate()
    {
        std::cout << "Use Destructor of Interest Rate" << std::endl;
    }
    
    void InterestRate::print_IR() const
    {
        std::cout << "The Interest Rate is: " << m_IR_value << std::endl;
    }
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS DIVIDEND YIELD
    //////////////////////////////////////////////////////
    
    DividendYield::DividendYield(const double DY)
    : m_DY_value(DY)
    {
        std::cout << "Use Constructor of DividendYield" << std::endl;
    }
    
    DividendYield::~DividendYield()
    {
        std::cout << "Use Destructor of DividendYield" << std::endl;
    }
    
    void DividendYield::print_DY() const
    {
        std::cout << "The DividendYield is: " << m_DY_value << std::endl;
    }
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS SPOT
    //////////////////////////////////////////////////////
    
    Spot::Spot(const double val)
    : m_Spot_value(val)
    {
        std::cout << "Use Constructor of Spot" << std::endl;
    }
    
    Spot::~Spot()
    {
        std::cout << "Use Destructor of Spot" << std::endl;
    }
    
    void Spot::print_Spot() const
    {
        std::cout << "The Spot is: " << m_Spot_value << std::endl;
    }
    
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS STRIKES
    //////////////////////////////////////////////////////
    
    Strikes::Strikes(const std::vector<double> strikes)
    : m_Strikes_value(strikes)
    {
        std::cout << "Use Constructor of Strikes" << std::endl;
    }
    
    Strikes::~Strikes()
    {
        std::cout << "Use Destructor of Strikes" << std::endl;
    }
    
    void Strikes::print_Strikes() const
    {
        std::cout << "Strikes: (";
        std:copy(m_Strikes_value.begin(), m_Strikes_value.end(), std::ostream_iterator<double>(std::cout,","));
        std::cout << ")" << std::endl;
    }

    
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS VOLATILITY
    //////////////////////////////////////////////////////
    
    Volatility::Volatility(const double vol)
    : m_Volatility_value(vol)
    {
        std::cout << "Use Constructor of Volatility" << std::endl;
    }
    
    Volatility::~Volatility()
    {
        std::cout << "Use Destructor of Volatility" << std::endl;
    }
    
    void Volatility::print_Volatility() const
    {
        std::cout << "The Volatility is: " << m_Volatility_value << std::endl;
    }
    
    
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS MATURITY
    //////////////////////////////////////////////////////
    
    Maturity::Maturity(const double maturity)
    : m_Maturity_value(maturity)
    {
        std::cout << "Use Constructor of Maturity" << std::endl;
    }
    
    Maturity::~Maturity()
    {
        std::cout << "Use Destructor of Maturity" << std::endl;
    }
    
    void Maturity::print_Maturity() const
    {
        std::cout << "The Maturity is: " << m_Maturity_value << std::endl;
    }
    
    
    
}
