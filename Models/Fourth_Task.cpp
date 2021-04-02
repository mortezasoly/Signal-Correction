#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "TimeSeriesData.h"
#include "AbstractBackgroundModel.h"
#include "AverageDiscretizedModel.h"


int main(int arg, char** argv)
{
    //Initilizing Average Background Model with 3d argument of command-line (smoothing parameter)
    AverageDiscretizedModel avg_model(std::stoi(argv[3]));
    

    /* 
    An Exception Module mainly intended to catch an exception, 
    when no files with declared names in as commandline arguments are not found
    */


    try
    {
        
        TimeSeriesData background_signal(argv[1]);   // Background Signal Initialization( Reading from file)
        TimeSeriesData input_signal(argv[2]); // Input Signal Initialization( Reading from file)

        /*
        Feeding background signal cycle by cycle to Model
        */

        for (int  i = 0; i < NUMBER_OF_CYCLES; i++)
        {
            
            avg_model.addCycle(background_signal);  // Feeding a cycle to model
            for (int j  = 0; j < SAMPLES_PER_CYCLE_AVERAGE; j++)
            {
            
                avg_model.update_background_cycle(j);
            }
            std::cout << "Processing " << avg_model.return_cycle_number() << "th cycle is completed.\n";

        }
        
        /*
        making background model, substracting it from input signal and writing it to file
        */

        TimeSeriesData backgroundmodel = avg_model.createData(NUMBER_OF_CYCLES);
        TimeSeriesData substracted = input_signal - backgroundmodel; // Substraction of modeled background from signal
        write_series_to_file(substracted, "Fourth_Task.txt");        // Writing it to a file
    }
    
    catch (std::exception &ex) 
    {
        std::cout << "Some Error Occured: "<< ex.what() << "!\n";
    }



    return 0;

}