#include "dates.hpp"

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

//// Inline definitions ////
date::date(){year_ = 0; month_ = 0; day_ = 0;};

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

// COMPARISONS //
bool operator == (const date& d1, const date& d2)
// checks for equality between two dates
{
    if(!d1.valid()||!d2.valid()) return false;
    if ((d1.day()==d2.day()) && (d1.month()==d2.month()) && (d1.year()==d2.year())) return true;
    return false;
}

bool operator != (const date& d1, const date& d2)
// We use the previous function to check for inequality
{
    if(!d1.valid()||!d2.valid()) return false;
    return !(d1==d2);
}

bool operator < (const date& d1, const date& d2)
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


bool operator <= (const date& d1, const date& d2)
{
    if(!d1.valid()||!d2.valid()) return false;
    if (d1==d2) return true;
    return (d1<d2);
}

bool operator > (const date& d1, const date& d2)
{
    if(!d1.valid()||!d2.valid()) return false;
    return !(d1<=d2);
}

bool operator >= (const date& d1, const date& d2)
{
    if(!d1.valid()||!d2.valid()) return false;
    return !(d1<d2);
}

// ITERATIONS //
inline date next_date(const date& d)
{
    date ndat;
    if(!d.valid()) return ndat; // return 0
    ndat=date((d.day()+1), d.month(), d.year()); if (ndat.valid()) return ndat;
    ndat=date(1, (d.month()+1), d.year()); if (ndat.valid()) return ndat;
    ndat=date(1,1,(d.year()+1)); return ndat;
}

inline date previous_date(const date& d)
{
    date ndat;
    if(!d.valid()) return ndat;
    ndat=date((d.day()-1), d.month(), d.year()); if (ndat.valid()) return ndat;
    ndat=date(31, (d.month()-1), d.year()); if (ndat.valid()) return ndat;
    ndat=date(30, (d.month()-1), d.year()); if (ndat.valid()) return ndat;
    ndat=date(29, (d.month()-1), d.year()); if (ndat.valid()) return ndat;
    ndat=date(28, (d.month()-1), d.year()); if (ndat.valid()) return ndat;
    ndat=date(31,12,(d.year()-1)); return ndat;
}

date date::operator ++(int) // postfix incrementation operator
{
    date d = *this;
    *this = next_date(*this);
    return d;
}

date date::operator ++() // prefix operator
{
    *this = next_date(*this);
    return *this;
}

date date::operator --(int) // postfix decrementation operator
{
    date d = *this;
    *this = previous_date(*this);
    return d;
}

date date::operator --() // prefix decrementation operator
{
    *this = previous_date(*this);
    return *this;
}

ostream& operator << (ostream& os, const date& d)
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

date operator + (const date& d, const int& days)
{
    if(!d.valid()) return date();
    if (days <0) return d-(-days);
    date temp=d;
    for (int i=1;i<=days;++i)
    {
        temp=next_date(temp);
    };
    return temp;
}

date operator += (const date& d, const int& days)
{
    return (d+days);
}

date operator - (const date& d, const int& days)
{
    if(!d.valid()) return date();
    if (days <0) return d-(-days);
    date temp=d;
    for (int i=1;i<=days;++i)
    {
        temp=previous_date(temp);
    };
    return temp;
}

date operator -= (const date& d, const int& days)
{
    return (d-days);
}

int operator - (const date& d1, const date& d2)
{
    if(!d1.valid()||!d2.valid()) return 0;
    cout << "Invalid date /n";
    if (d1==d2) return 0;
    else if (d1>d2)
    {
        date temp=d1;
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
        date temp=d1;
        int i=0;
        while (temp<d2)
        {
            --i;
            temp=next_date(temp);
        }
        return i;
    };
}
