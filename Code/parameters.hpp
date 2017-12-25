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
        virtual ~InterestRate();
        
        void print_IR() const;
        
        InterestRate(const InterestRate& rhs) = delete;
        InterestRate& operator=(const InterestRate& rhs) = delete;
        InterestRate(InterestRate&& rhs) = delete;
        InterestRate& operator=(InterestRate&& rhs) = delete;
    protected:
        InterestRate(const double IR);
    private:
        double m_IR_value;
    };
    
    class DividendYield
    {
    public:
        virtual ~DividendYield();
        
        void print_DY() const;
        
        DividendYield(const DividendYield& rhs) = delete;
        DividendYield& operator=(const DividendYield& rhs) = delete;
        DividendYield(DividendYield&& rhs) = delete;
        DividendYield& operator=(DividendYield&& rhs) = delete;
    protected:
        DividendYield(const double DY);
    private:
        double m_DY_value;
    };
    
    class Spot
    {
    public:
        virtual ~Spot();
        
        void print_Spot() const;
        
        Spot(const Spot& rhs) = delete;
        Spot& operator=(const Spot& rhs) = delete;
        Spot(Spot&& rhs) = delete;
        Spot& operator=(Spot&& rhs) = delete;
    protected:
        Spot(const double val);
    private:
        double m_Spot_value;
    };
    
    class Strikes
    {
    public:
        virtual ~Strikes();
        
        void print_Strikes() const;
        
        Strikes(const Strikes& rhs) = delete;
        Strikes& operator=(const Strikes& rhs) = delete;
        Strikes(Strikes&& rhs) = delete;
        Strikes& operator=(Strikes&& rhs) = delete;
    protected:
        Strikes(const std::vector<double> strikes);
    private:
        std::vector<double> m_Strikes_value;
    };
    
    class Volatility
    {
    public:
        virtual ~Volatility();
        
        void print_Volatility() const;
        
        Volatility(const Volatility& rhs) = delete;
        Volatility& operator=(const Volatility& rhs) = delete;
        Volatility(Volatility&& rhs) = delete;
        Volatility& operator=(Volatility&& rhs) = delete;
    protected:
        Volatility(const double vol);
    private:
        double m_Volatility_value;
    };
    
    class Maturity
    {
    public:
        virtual ~Maturity();
        
        void print_Maturity() const;
        
        Maturity(const Maturity& rhs) = delete;
        Maturity& operator=(const Maturity& rhs) = delete;
        Maturity(Maturity&& rhs) = delete;
        Maturity& operator=(Maturity&& rhs) = delete;
    protected:
        Maturity(const double maturity);
    private:
        double m_Maturity_value;
    };
}


#endif
