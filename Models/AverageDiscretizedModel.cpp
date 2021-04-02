#include "AverageDiscretizedModel.h"
#include <iostream>


/*
Constructor to initialize AverageModel
with a value for smoothing parameter
and a 2D vector to save background moedeled signal
( based on dimensions of input signal, i.e 50 * 200 )
for later reccurent and later use
*/

AverageDiscretizedModel::AverageDiscretizedModel(double value):
    smoothing_parameter(value),
    cycle_number(0),
    modeled_cycles(NUMBER_OF_CYCLES, std::vector<double>(SAMPLES_PER_CYCLE_AVERAGE))
{
    
}

/*
Evaluate Background Model
Saving to 2-D vector of modeled_cycle
done in another function
*/

double AverageDiscretizedModel::evaluateBackground(int i) const
{
    if (cycle_number == 1)
    {
        const double x = current_cycle[i];
        return x;
    }
    else
    {   /* 
        Using smooth parameter to create average background evaluation
        */
        const double x = smoothing_parameter * current_cycle[i] - (1-smoothing_parameter)*modeled_cycles[cycle_number - 2][i];
        return x;
    }
    
    
}
void AverageDiscretizedModel::update_background_cycle(int i )
{   
    /*
    Update of average background model and saving in modeled_cycle
    done here
    */

    modeled_cycles[cycle_number - 1][i] = evaluateBackground(i);
}



/*
getting current cycle from data, both the signal and time steps
to feed (also save) to the model
*/

void AverageDiscretizedModel::addCycle(TimeSeriesData sample_data) 
{
    if((cycle_number + 1) * SAMPLES_PER_CYCLE_AVERAGE > sample_data.return_size())
    {
        std::cout << "No more cycles in input signal existing" << '\n';
        return;
    }

    else
    {
        int m = cycle_number * SAMPLES_PER_CYCLE_AVERAGE;       // begining of cycle
        int n = (cycle_number + 1) * SAMPLES_PER_CYCLE_AVERAGE; // ending of cycle

        /*
        using iterators and values of m and n to retrieve cycles of signal
        from input data
        (also time steps)
        */

        std::vector<double>::const_iterator first_signal = (sample_data.return_signal_vector()).begin() + m;
        std::vector<double>::const_iterator last_signal = (sample_data.return_signal_vector()).begin() + n;
        std::vector<double> tmp(first_signal, last_signal);

        std::vector<double>::const_iterator first_time = (sample_data.return_time_vector()).begin() + m;
        std::vector<double>::const_iterator last_time= (sample_data.return_time_vector()).begin() + n;
        std::vector<double> tmp_time(first_time, last_time);

        /*
        Saving time-step cycle for later use in creation of TimeSeriesData
        Also updating the current cycle for evaluation
        */
        retrieved_time_steps.push_back(tmp_time);
        current_cycle = tmp;
    }
    
    ++cycle_number; // updating the cycle number in order to next time beging from this cycle
    
}


int AverageDiscretizedModel::return_cycle_number()
{
    return cycle_number;
}


/*
Create TimeSeries Data from
time-steps which already save in class plus
evaulated average background model
*/

TimeSeriesData AverageDiscretizedModel::createData(int nCycles)
{
    std::vector<double> time_steps;
    std::vector<double> modeled_signal;
    
    for (int  i = 0; i < nCycles; i++)
    {
       
        time_steps.insert(std::end(time_steps), std::begin(retrieved_time_steps[i]), std::end(retrieved_time_steps[i]));
        modeled_signal.insert(std::end(modeled_signal), std::begin(modeled_cycles[i]), std::end(modeled_cycles[i]));
    }


    TimeSeriesData new_data(modeled_signal, time_steps);
    return new_data;

    
}

