#include "MockFittedBackgroundModel.h"

/*
Constructor for model
and Initialization of 2-D vector for saving
background evaluated signal ( however not needed!)
*/
MockFittedBackgroundModel::MockFittedBackgroundModel(
    double A , double f, double offset, double phase):
        A(A),
        f(f), 
        offset(offset), phase(phase), cycle_number(0), 
        modeled_cycles(NUMBER_OF_CYCLES_MOCK, std::vector<double>(SAMPLES_PER_CYCLE))
{

}

double MockFittedBackgroundModel::evaluateBackground(int i) const 
{
    double dt = 1.0  / SAMPLES_PER_CYCLE / f;
    return A * sin(2.0 * M_PI * f * i * dt + phase) + offset;
}    


/* 
Adding cycles of input signals
to be evaluated and time-steps to be saved
for later use in creation of time-series
*/
void MockFittedBackgroundModel::addCycle(TimeSeriesData sample_data) 
{
    if((cycle_number + 1) * SAMPLES_PER_CYCLE > sample_data.return_size())
    {
        std::cout << "No more cycles existing" << '\n';
        return;
    }

    else
    {
        int m = cycle_number * SAMPLES_PER_CYCLE;
        int n = (cycle_number + 1) * SAMPLES_PER_CYCLE;

        std::vector<double>::const_iterator first_signal = (sample_data.return_signal_vector()).begin() + m;
        std::vector<double>::const_iterator last_signal = (sample_data.return_signal_vector()).begin() + n;
        std::vector<double> tmp(first_signal, last_signal);

        std::vector<double>::const_iterator first_time = (sample_data.return_time_vector()).begin() + m;
        std::vector<double>::const_iterator last_time= (sample_data.return_time_vector()).begin() + n;
        std::vector<double> tmp_time(first_time, last_time);
    
        retrieved_time_steps.push_back(tmp_time);
        
        current_cycle = tmp;
    }

    ++cycle_number;
    
}

int MockFittedBackgroundModel::return_cycle_number()
{
    return cycle_number;
}

void MockFittedBackgroundModel::update_background_cycle( int i )
{
    modeled_cycles[cycle_number - 1][i] = evaluateBackground(i);
}


TimeSeriesData MockFittedBackgroundModel::createData(int nCycles)
{
    std::vector<double> time_steps;
    std::vector<double> modeled_signal;
    
    for (int  i = 0; i < nCycles; i++)
    {
        /* code */
        time_steps.insert(std::end(time_steps), std::begin(retrieved_time_steps[i]), std::end(retrieved_time_steps[i]));
        modeled_signal.insert(std::end(modeled_signal), std::begin(modeled_cycles[i]), std::end(modeled_cycles[i]));
    }


    TimeSeriesData new_data(time_steps, modeled_signal);
    return new_data;
    
    
}
