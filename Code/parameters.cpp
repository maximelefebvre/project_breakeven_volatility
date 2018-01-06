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

    }
    
    InterestRate::~InterestRate()
    {
        m_IR_value = 0;
    }
    
    InterestRate::InterestRate(const InterestRate& rhs)
    : m_IR_value(rhs.m_IR_value)
    {
        
    }
    
    InterestRate& InterestRate::operator=(const InterestRate& rhs)
    {
        m_IR_value = rhs.m_IR_value;
    }
    
    InterestRate::InterestRate(InterestRate&& rhs)
    : m_IR_value(std::move(rhs.m_IR_value))
    {
        
    }
    
    InterestRate& InterestRate::operator=(InterestRate&& rhs)
    {
        std::swap(m_IR_value,rhs.m_IR_value);
    }
    
    void InterestRate::print_IR() const
    {
        std::cout << "The Interest Rate is: " << m_IR_value << std::endl;
    }
    
    double InterestRate::value() const
    {
        return m_IR_value;
    }
    
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS DIVIDEND YIELD
    //////////////////////////////////////////////////////
    
    DividendYield::DividendYield(const double DY)
    : m_DY_value(DY)
    {

    }
    
    DividendYield::~DividendYield()
    {
        m_DY_value = 0;
    }
    
    DividendYield::DividendYield(const DividendYield& rhs)
    : m_DY_value(rhs.m_DY_value)
    {
        
    }
    
    DividendYield& DividendYield::operator=(const DividendYield& rhs)
    {
        m_DY_value = rhs.m_DY_value;
    }
    
    DividendYield::DividendYield(DividendYield&& rhs)
    : m_DY_value(std::move(rhs.m_DY_value))
    {
        
    }
    
    DividendYield& DividendYield::operator=(DividendYield&& rhs)
    {
        std::swap(m_DY_value,rhs.m_DY_value);
    }
    
    void DividendYield::print_DY() const
    {
        std::cout << "The DividendYield is: " << m_DY_value << std::endl;
    }
    
    double DividendYield::value() const
    {
        return m_DY_value;
    }
    
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS SPOT
    //////////////////////////////////////////////////////
    
    Spot::Spot(const double val)
    : m_Spot_value(val)
    {

    }
    
    Spot::~Spot()
    {
        m_Spot_value = 0;
    }
    
    Spot::Spot(const Spot& rhs)
    : m_Spot_value(rhs.m_Spot_value)
    {
        
    }
    
    Spot& Spot::operator=(const Spot& rhs)
    {
        m_Spot_value = rhs.m_Spot_value;
    }
    
    Spot::Spot(Spot&& rhs)
    : m_Spot_value(std::move(rhs.m_Spot_value))
    {
        
    }
    
    Spot& Spot::operator=(Spot&& rhs)
    {
        std::swap(m_Spot_value,rhs.m_Spot_value);
    }
    
    void Spot::print_Spot() const
    {
        std::cout << "The Spot is: " << m_Spot_value << std::endl;
    }
    
    double Spot::value() const
    {
        return m_Spot_value;
    }
    
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS STRIKES
    //////////////////////////////////////////////////////
    
    Strike::Strike(const double strike)
    : m_Strike_value(strike)
    {

    }
    
    Strike::~Strike()
    {
        m_Strike_value = 0;
    }
    
    Strike::Strike(const Strike& rhs)
    : m_Strike_value(rhs.m_Strike_value)
    {
        
    }
    
    Strike& Strike::operator=(const Strike& rhs)
    {
        m_Strike_value = rhs.m_Strike_value;
    }
    
    Strike::Strike(Strike&& rhs)
    : m_Strike_value(std::move(rhs.m_Strike_value))
    {
        
    }
    
    Strike& Strike::operator=(Strike&& rhs)
    {
        std::swap(m_Strike_value,rhs.m_Strike_value);
    }
    
    void Strike::print_Strike() const
    {
        std::cout << "The Strike is: " << m_Strike_value << std::endl;
    }
    
    double Strike::value() const
    {
        return m_Strike_value;
    }
    
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS VOLATILITY
    //////////////////////////////////////////////////////
    
    Volatility::Volatility(const double vol)
    : m_Volatility_value(vol)
    {

    }
    
    Volatility::~Volatility()
    {
        m_Volatility_value = 0;
    }
    
    Volatility::Volatility(const Volatility& rhs)
    : m_Volatility_value(rhs.m_Volatility_value)
    {
        
    }
    
    Volatility& Volatility::operator=(const Volatility& rhs)
    {
        m_Volatility_value = rhs.m_Volatility_value;
    }
    
    Volatility::Volatility(Volatility&& rhs)
    : m_Volatility_value(std::move(rhs.m_Volatility_value))
    {
        
    }
    
    Volatility& Volatility::operator=(Volatility&& rhs)
    {
        std::swap(m_Volatility_value,rhs.m_Volatility_value);
    }
    
    void Volatility::print_Volatility() const
    {
        std::cout << "The Volatility is: " << m_Volatility_value << std::endl;
    }
    
    double Volatility::value() const
    {
        return m_Volatility_value;
    }
    
    
    
    //////////////////////////////////////////////////////
    /////////////// CLASS MATURITY
    //////////////////////////////////////////////////////
    
    Maturity::Maturity(const double maturity)
    : m_Maturity_value(maturity)
    {

    }
    
    Maturity::~Maturity()
    {
        m_Maturity_value = 0;
    }
    
    Maturity::Maturity(const Maturity& rhs)
    : m_Maturity_value(rhs.m_Maturity_value)
    {
        
    }
    
    Maturity& Maturity::operator=(const Maturity& rhs)
    {
        m_Maturity_value = rhs.m_Maturity_value;
    }
    
    Maturity::Maturity(Maturity&& rhs)
    : m_Maturity_value(std::move(rhs.m_Maturity_value))
    {
        
    }
    
    Maturity& Maturity::operator=(Maturity&& rhs)
    {
        std::swap(m_Maturity_value,rhs.m_Maturity_value);
    }
    
    void Maturity::print_Maturity() const
    {
        std::cout << "The Maturity is: " << m_Maturity_value << std::endl;
    }
    
    double Maturity::value() const
    {
        return m_Maturity_value;
    }
    
    
    
}
