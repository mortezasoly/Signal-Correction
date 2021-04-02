#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "TimeSeriesData.h"
#include "AbstractBackgroundModel.h"
#include "MockFittedBackgroundModel.h"



int main(int arg, char** argv)
{
    
    try
    {
        /*
        Creation of timeseries data from existing input file
        using related constructor
        */
        TimeSeriesData input_signal(argv[1]);
        MockFittedBackgroundModel mock_model;
    
        int number_of_cycles = 50;

        /*
        Evaluation of background model
        cycle by cycle
        */
        for (int  i = 0; i < number_of_cycles; i++)
        {
        /* code */
            mock_model.addCycle(input_signal);
            for (int j  = 0; j < SAMPLES_PER_CYCLE; j++)
            {
                
                mock_model.update_background_cycle(j);
            
            }

            std::cout << "Processing " <<  mock_model.return_cycle_number() << "th cycle is completed.\n";
        }
        /*
        Creating evaulated timeseries from background model
        Then substracting it from input signal
        */
        TimeSeriesData backgroundmodel = mock_model.createData(number_of_cycles);
        TimeSeriesData substracted = input_signal - backgroundmodel;
        write_series_to_file(substracted, "Third_Task.txt");
        
    }

    catch(const std::exception& e)
    {
        std::cerr << "Some Error found: " << e.what() << '\n';
    }
    
    
    

    return 0;

}