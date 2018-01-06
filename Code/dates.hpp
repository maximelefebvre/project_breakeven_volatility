#ifndef DATES_HPP
#define DATES_HPP

#include <iostream>
using namespace std;

class date
{
public:
    date();
    date(const int& d, const int& mm, const int& yyyy);
    
    bool valid(void) const;
    
    int day() const;
    int month() const;
    int year() const;
    
    void set_day(const int& day );
    void set_month(const int& month );
    void set_year(const int& year);
    
    date operator ++();
    date operator ++(int);
    date operator --();
    date operator --(int);
    
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

ostream& operator << ( ostream& os, const date& d); //output operator

#endif
