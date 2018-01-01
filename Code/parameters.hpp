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
    
        //InterestRate(const InterestRate& rhs) = delete;
        //InterestRate& operator=(const InterestRate& rhs) = delete;
        //InterestRate(InterestRate&& rhs) = delete;
        //InterestRate& operator=(InterestRate&& rhs) = delete;
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
        
        //DividendYield(const DividendYield& rhs) = delete;
        //DividendYield& operator=(const DividendYield& rhs) = delete;
        //DividendYield(DividendYield&& rhs) = delete;
        //DividendYield& operator=(DividendYield&& rhs) = delete;
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
        
        //Spot(const Spot& rhs) = delete;
        //Spot& operator=(const Spot& rhs) = delete;
        //Spot(Spot&& rhs) = delete;
        //Spot& operator=(Spot&& rhs) = delete;
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
        
        //Strike(const Strike& rhs) = delete;
        //Strike& operator=(const Strike& rhs) = delete;
        //Strike(Strike&& rhs) = delete;
        //Strike& operator=(Strike&& rhs) = delete;
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
        
        //Volatility(const Volatility& rhs) = delete;
        //Volatility& operator=(const Volatility& rhs) = delete;
        //Volatility(Volatility&& rhs) = delete;
        //Volatility& operator=(Volatility&& rhs) = delete;
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
        
        //Maturity(const Maturity& rhs) = delete;
        //Maturity& operator=(const Maturity& rhs) = delete;
        //Maturity(Maturity&& rhs) = delete;
        //Maturity& operator=(Maturity&& rhs) = delete;
    protected:
    private:
        double m_Maturity_value;
    };
}


#endif
