#include "dates.hpp"

// DEFINING THE BASIC OPERATIONS //
//// Construction //
date:date(const int& dd, const int& mm, const int& yyyy)
{
    day_ = dd
    month_ = mm
    year_ = yyyy // User must give year fully (4 digits)
};

//// Inline definitions ////
date::date(){year_ = 0, month_ = 0, day_ = 0};

int date::day() const
{
    return day_;
};

int date::month() const
{
    return month_;
};

int date::year const
{
    return year_;
};

void set_day(const int& day )
{
    date::day_ = day;
};

void set_month(const int& month )
{
    date::month_ = month;
};

void set_year(const int& year )
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
        else // both dates have the same month
        {
            if(d1.day()<d2.day()) return true;
            else return false;
        };
    };
    return false
}


bool operator <= (const date& d1, const date& d2)
{
    if(!d1.valid()||!d2.valid()) return false;
    if d1==d2 return true;
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
