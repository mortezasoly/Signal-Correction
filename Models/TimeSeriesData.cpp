#include "TimeSeriesData.h"



/*
A constructor to initialize time series object from a file 
give the file's name
*/

TimeSeriesData::TimeSeriesData(std::string files_name)
{
    
    std::ifstream my_file;  
    my_file.open(files_name);

    /*
    Throwing an exception if the file doesn't exit 
    or cannot be opened
    */

    if(!my_file)
    {
        throw std::runtime_error("Could not open file: " + files_name);
    }
    


    /*
    Reading file line by line.
    Using "stringstream" method given the knowledge about
    the structure of the file.
    */

    std::string line;
    double input;
    if(my_file.is_open())
    {
        std::getline(my_file,line);
        while(std::getline(my_file,line))
        {
            std::stringstream my_stream(line);

            my_stream >> input; // First read time step
            time_points.push_back(input);
            
            my_stream >> input; // Second read the signal value
            signal_values.push_back(input);
        }

        my_file.close();
    }


}

/*
A constructor for time series object give two numeric vectors
which one indicates time steps, the other values of signal.
Useful when creating and editing timeseries
*/

TimeSeriesData::TimeSeriesData(std::vector<double> m_signal_values, std::vector<double> m_time_points):
    signal_values(m_signal_values), time_points(m_time_points)
{
    
}

/* 
A function to return signal values in the time series object
*/

std::vector<double> TimeSeriesData::return_signal_vector() const
{
    return signal_values;
}


/*
A function to return time steps in time series object
*/

std::vector<double> TimeSeriesData::return_time_vector() const 
{
    return time_points;
}


/*
a function to write a time series to a txt file given name
*/


void write_series_to_file(TimeSeriesData& my_data, std::string files_name)
{

    std::ofstream new_file;
    new_file.open(files_name);


    new_file << "# Time" << ' ' << "Signal" << '\n';        // header of the file

    std::vector<double> time;
    time = my_data.return_time_vector();


    for(int j = 0; j < my_data.return_size(); ++j)
    {
        new_file << time[j] << '\t' << my_data[j] << '\n'; // writing signal values to file line by line
    }

    new_file.close();

}

/*
Overloading substraction for time series object considering 
if they have same time steps and same size. Otherwise dangerous!
*/

TimeSeriesData operator-(const TimeSeriesData &c1, const TimeSeriesData &c2)
{
    std::vector<double> time_steps = c1.return_time_vector();
    std::vector<double> c1_signal  = c1.return_signal_vector();
    std::vector<double> c2_signal  = c2.return_signal_vector();
    std::vector<double> substract;
    for(int i = 0; i < c1_signal.size(); ++i)
    {
        substract.push_back(c1_signal[i] - c2_signal[i]);

    }

    TimeSeriesData substracted_time_series(substract, time_steps);
    return substracted_time_series;

}