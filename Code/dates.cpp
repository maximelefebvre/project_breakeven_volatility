#include "dates.hpp"

namespace std
{
    // DEFINING THE BASIC OPERATIONS //
    //// Construction //
    date::date(const int& dd, const int& mm, const int& yyyy)
    {
        day_ = dd;
        month_ = mm;
        year_ = yyyy; // User must give year fully (4 digits)
    };
    
    date::~date()
    {
        day_ = 0;
        month_ = 0;
        year_ = 0;
    }
    
    date::date(const date& rhs)
    : day_(rhs.day_), month_(rhs.month_), year_(rhs.year_)
    {
        
    }
    
    date& date::operator=(const date& rhs)
    {
        day_ = rhs.day_;
        month_ = rhs.month_;
        year_ = rhs.year_;
    }
    
    date::date(date&& rhs)
    : day_(std::move(rhs.day_)), month_(std::move(rhs.month_)), year_(std::move(rhs.year_))
    {
        
    }
    
    date& date::operator=(date&& rhs)
    {
        std::swap(day_,rhs.day_);
        std::swap(month_,rhs.month_);
        std::swap(year_,rhs.year_);
    }
    
    //// Inline definitions ////
    date::date(){day_ = 0; month_ = 0; year_ = 0;};
    
    int date::day() const
    {
        return day_;
    };
    
    int date::month() const
    {
        return month_;
    };
    
    int date::year() const
    {
        return year_;
    };
    
    void date::set_day(const int& day )
    {
        date::day_ = day;
    };
    
    void date::set_month(const int& month )
    {
        date::month_ = month;
    };
    
    void date::set_year(const int& year )
    {
        date::year_ = year;
    };
    
    bool date::valid(void) const // Checks the validity of the year
    {
        if (year_ < 0) return false;
        if (month_ > 12 || month_ < 1) return false;
        if (day_ > 31|| day_ < 1) return false;
        if (day_==31 && (month_==2||month_==4||month_==6||month_==9||month_==11)) return false;
        if (day_==30 && month_==2) return false;
        if ((day_==29 && month_==2) &&
            (year_%4!=0||(year_%100==0 && year_%400!=0))) return false;
        return true;
    }
}

// COMPARISONS //
bool operator == (const std::date& d1, const std::date& d2)
// checks for equality between two dates
{
    if(!d1.valid()||!d2.valid()) return false;
    if ((d1.day()==d2.day()) && (d1.month()==d2.month()) && (d1.year()==d2.year())) return true;
    return false;
}

bool operator != (const std::date& d1, const std::date& d2)
// We use the previous function to check for inequality
{
    if(!d1.valid()||!d2.valid()) return false;
    return !(d1==d2);
}

bool operator < (const std::date& d1, const std::date& d2)
{
    if(!d1.valid()||!d2.valid()) return false;
    if(d1.year()<d2.year()) return true;
    else if (d1.year()>d2.year()) return false;
    else // both dates have the same year
    {
        if(d1.month()<d2.month()) return true;
        else if (d1.month()>d2.month()) return false;
        else // both dates have the same year and month
        {
            if(d1.day()<d2.day()) return true;
            else return false;
        };
    };
    return false;
}


bool operator <= (const std::date& d1, const std::date& d2)
{
    if(!d1.valid()||!d2.valid()) return false;
    if (d1==d2) return true;
    return (d1<d2);
}

bool operator > (const std::date& d1, const std::date& d2)
{
    if(!d1.valid()||!d2.valid()) return false;
    return !(d1<=d2);
}

bool operator >= (const std::date& d1, const std::date& d2)
{
    if(!d1.valid()||!d2.valid()) return false;
    return !(d1<d2);
}

// ITERATIONS //
inline std::date next_date(const std::date& d)
{
    std::date ndat;
    if(!d.valid()) return ndat; // return 0
    ndat=std::date((d.day()+1), d.month(), d.year()); if (ndat.valid()) return ndat;
    ndat=std::date(1, (d.month()+1), d.year()); if (ndat.valid()) return ndat;
    ndat=std::date(1,1,(d.year()+1)); return ndat;
}

inline std::date previous_date(const std::date& d)
{
    std::date ndat;
    if(!d.valid()) return ndat;
    ndat=std::date((d.day()-1), d.month(), d.year()); if (ndat.valid()) return ndat;
    ndat=std::date(31, (d.month()-1), d.year()); if (ndat.valid()) return ndat;
    ndat=std::date(30, (d.month()-1), d.year()); if (ndat.valid()) return ndat;
    ndat=std::date(29, (d.month()-1), d.year()); if (ndat.valid()) return ndat;
    ndat=std::date(28, (d.month()-1), d.year()); if (ndat.valid()) return ndat;
    ndat=std::date(31,12,(d.year()-1)); return ndat;
}

std::date std::date::operator ++(int) // postfix incrementation operator
{
    std::date d = *this;
    *this = next_date(*this);
    return d;
}

std::date std::date::operator ++() // prefix operator
{
    *this = next_date(*this);
    return *this;
}

std::date std::date::operator --(int) // postfix decrementation operator
{
    std::date d = *this;
    *this = previous_date(*this);
    return d;
}

std::date std::date::operator --() // prefix decrementation operator
{
    *this = previous_date(*this);
    return *this;
}

std::ostream& operator << (std::ostream& os, const std::date& d)
{
    if(d.valid())
    {
        os<< d.day() << "/" << d.month() << "/" << d.year();
    }
    else
    {
        os << "Invalid date";
    };
    return os;
}

std::date operator + (const std::date& d, const int& days)
{
    if(!d.valid()) return std::date();
    if (days <0) return d-(-days);
    std::date temp=d;
    for (int i=1;i<=days;++i)
    {
        temp=next_date(temp);
    };
    return temp;
}

std::date operator += (const std::date& d, const int& days)
{
    return (d+days);
}

std::date operator - (const std::date& d, const int& days)
{
    if(!d.valid()) return std::date();
    if (days <0) return d-(-days);
    std::date temp=d;
    for (int i=1;i<=days;++i)
    {
        temp=previous_date(temp);
    };
    return temp;
}

std::date operator -= (const std::date& d, const int& days)
{
    return (d-days);
}

int operator - (const std::date& d1, const std::date& d2)
{
    if(!d1.valid()||!d2.valid())
    {
        return 0;
        std::cout << "Invalid date!" << std::endl;
    }
    if (d1==d2) return 0;
    else if (d1>d2)
    {
        std::date temp=d1;
        int i=0;
        while (temp>d2)
        {
            ++i;
            temp=previous_date(temp);
        }
        return i;
    }
    else
    {
        std::date temp=d1;
        int i=0;
        while (temp<d2)
        {
            --i;
            temp=next_date(temp);
        }
        return i;
    };
}
