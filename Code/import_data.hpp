#ifndef IMPORT_DATA_HPP
#define IMPORT_DATA_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace data_importation
{
    typedef std::vector <double> record_t;
    typedef std::vector <record_t> data_t;
    
    std::istream& operator >> ( std::istream& ins, record_t& record );
    std::istream& operator >> ( std::istream& ins, data_t& data );
    data_t get_data(std::string NameOfTheFile);
}

#endif

