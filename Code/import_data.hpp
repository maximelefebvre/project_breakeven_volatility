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
    std::istream& operator >> ( std::istream& ins, record_t& record );
    std::istream& operator >> ( std::istream& ins, data_t& data );
    std::vector<double> get_data(std::string NameOfTheFile);
}

#endif

