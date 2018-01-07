#ifndef DATES_HPP
#define DATES_HPP

#include <iostream>
using namespace std;

class date
{
public:
    date();
    date(const int& d, const int& mm, const int& yyyy);
    virtual ~date();
    
    date(const date& rhs);
    date& operator=(const date& rhs);
    date(date&& rhs);
    date& operator=(date&& rhs);
    
    bool valid(void) const;
    
    int day() const;
    int month() const;
    int year() const;
    
    void set_day(const int& day );
    void set_month(const int& month );
    void set_year(const int& year);
    
    date operator ++(); // prefix operator
    date operator ++(int); // postfix operator
    date operator --(); // prefix operator
    date operator --(int); // postfix operator
    
protected:
    int year_;
    int month_;
    int day_;
};

// Comparison operators
bool operator == (const date&, const date&);
bool operator != (const date&, const date&);
bool operator < (const date&, const date&);
bool operator > (const date&, const date&);
bool operator <=(const date&, const date&);
bool operator >=(const date&, const date&);

// Calculation operators
date operator + (const date&, const int&); //int will be a number of days
date operator += (const date&, const int&);
date operator - (const date&, const int&);
date operator -= (const date&, const int&);
int operator - (const date&, const date&); // number of days between dates

ostream& operator << (ostream& os, const date& d); //output operator

#endif
