#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

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
    class InterestRate
    {
    public:
        InterestRate(const double IR);
        virtual ~InterestRate();
        
        void print_IR() const;
        double value() const;
    
        InterestRate(const InterestRate& rhs);
        InterestRate& operator=(const InterestRate& rhs);
        InterestRate(InterestRate&& rhs);
        InterestRate& operator=(InterestRate&& rhs);
    protected:
    private:
        double m_IR_value;
    };
    
    class DividendYield
    {
    public:
        DividendYield(const double DY);
        virtual ~DividendYield();
        
        void print_DY() const;
        double value() const;
        
        DividendYield(const DividendYield& rhs);
        DividendYield& operator=(const DividendYield& rhs);
        DividendYield(DividendYield&& rhs);
        DividendYield& operator=(DividendYield&& rhs);
    protected:
    private:
        double m_DY_value;
    };
    
    class Spot
    {
    public:
        Spot(const double val);
        virtual ~Spot();
        
        void print_Spot() const;
        double value() const;
        
        Spot(const Spot& rhs);
        Spot& operator=(const Spot& rhs);
        Spot(Spot&& rhs);
        Spot& operator=(Spot&& rhs);
    protected:
    private:
        double m_Spot_value;
    };
    
    class Strike
    {
    public:
        Strike(const double strike);
        virtual ~Strike();
        
        void print_Strike() const;
        double value() const;
        
        Strike(const Strike& rhs);
        Strike& operator=(const Strike& rhs);
        Strike(Strike&& rhs);
        Strike& operator=(Strike&& rhs);
    protected:
    private:
        double m_Strike_value;
    };
    
    class Volatility
    {
    public:
        Volatility(const double vol);
        virtual ~Volatility();
        
        void print_Volatility() const;
        double value() const;
        
        Volatility(const Volatility& rhs);
        Volatility& operator=(const Volatility& rhs);
        Volatility(Volatility&& rhs);
        Volatility& operator=(Volatility&& rhs);
    protected:
    private:
        double m_Volatility_value;
    };
    
    class Maturity
    {
    public:
        Maturity(const double maturity);
        virtual ~Maturity();
        
        void print_Maturity() const;
        double value() const;
        
        Maturity(const Maturity& rhs);
        Maturity& operator=(const Maturity& rhs);
        Maturity(Maturity&& rhs);
        Maturity& operator=(Maturity&& rhs);
    protected:
    private:
        double m_Maturity_value;
    };
}


#endif
