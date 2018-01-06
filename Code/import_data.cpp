#include "import_data.hpp"

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
    
    //-----------------------------------------------------------------------------
    // Let's overload the stream input operator to read a list of CSV fields (which a CSV record).
    // Remember, a record is a list of doubles separated by commas ','.
    std::istream& operator >> ( std::istream& ins, record_t& record )
    {
        // make sure that the returned record contains only the stuff we read now
        record.clear();
        
        // read the entire line into a string (a CSV record is terminated by a newline)
        std::string line;
        getline( ins, line );
        
        // now we'll use a stringstream to separate the fields out of the line
        std::stringstream ss( line );
        std::string field;
        while (getline( ss, field, ',' ))
        {
            // for each field we wish to convert it to a double
            // (since we require that the CSV contains nothing but floating-point values)
            std::stringstream fs( field );
            double f = 0.0;  // (default value is 0.0)
            fs >> f;
            
            // add the newly-converted field to the end of the record
            record.push_back( f );
        }
        
        // Now we have read a single line, converted into a list of fields, converted the fields
        // from strings to doubles, and stored the results in the argument record, so
        // we just return the argument stream as required for this kind of input overload function.
        return ins;
    }
    
    //-----------------------------------------------------------------------------
    // Let's likewise overload the stream input operator to read a list of CSV records.
    // This time it is a little easier, just because we only need to worry about reading
    // records, and not fields.
    std::istream& operator >> ( std::istream& ins, data_t& data )
    {
        // make sure that the returned data only contains the CSV data we read here
        data.clear();
        
        // For every record we can read from the file, append it to our resulting data
        record_t record;
        while (ins >> record)
        {
            data.push_back( record );
        }
        
        // Again, return the argument stream as required for this kind of input stream overload.
        return ins;
    }
    
    data_t get_data(std::string NameOfTheFile)
    {
        // Here is the data we want.
        data_t data;
        
        // Here is the file containing the data. Read it into data.
        std::ifstream infile( NameOfTheFile );
        infile >> data;
        
        // Complain if something went wrong.
        if (!infile.eof())
         {
         throw std::runtime_error("Problem with your data");
         }
        
        infile.close();
        
        // Otherwise, list some basic information about the file.
        std::cout << "Your CSV file contains " << data.size() << " records.\n";
        
        std::size_t max_record_size = 0;
        for (std::size_t i = 0; i < data.size(); ++i)
            if (max_record_size < data[i].size())
            {
                max_record_size = data[i].size();
            }
        std::cout << "The largest record has " << max_record_size << " fields.\n";
        
        std::cout << "The second field in the fourth record contains the value " << data[ 3 ][ 1 ] << ".\n";
        
        std::cout << "Good bye!\n";
        
        return data;
    }

}
