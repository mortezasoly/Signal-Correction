
#ifndef TIME_SERIES
#define TIME_SERIES
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>


class TimeSeriesData
{
private:
    /*
    Saving Time Series as two vector, one for
    values of the signal, one for the time-step
    */
    std::vector<double> signal_values;
    std::vector<double> time_points;

public:
    
    /*
    Constructor creating time series given a file's 
    name
    */
    TimeSeriesData(std::string files_name);

    /*
    Constructor creating time series given
    two vector for the values of the signal and time points
    */
    TimeSeriesData(std::vector<double> m_signal_values, std::vector<double> m_time_points);


    std::vector<double> return_signal_vector() const;
    std::vector<double> return_time_vector() const;
   
    
    int return_size()
    {
        return signal_values.size();
    }

    /*
    Overloading this operator 
    for later use of retrieving signal at certain index
    */
    double& operator[](size_t index)
    {
        if(index >= signal_values.size())
        {
            throw std::runtime_error("Index bigger than length of time series vector");
        }
        
        return signal_values[index];
    }


    
    /*
    Overloading binary substraction operator.
    Two time series considered to be equal size and having same time steps,
    otherwise useless.(dangerous!)
    Useful when substracting signals
    */

    friend TimeSeriesData operator-(const TimeSeriesData &c1, const TimeSeriesData &c2);

};


void write_series_to_file(TimeSeriesData& my_data, std::string files_name);

#endif
