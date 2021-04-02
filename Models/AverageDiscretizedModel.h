#ifndef AVG_DISC_MODEL
#define AVG_DISC_MODEL
#include "AbstractBackgroundModel.h"
#include <algorithm>
#include <iostream>

const int SAMPLES_PER_CYCLE_AVERAGE = 200;
const int NUMBER_OF_CYCLES = 50;

class AverageDiscretizedModel : private AbstractBackgroundModel
{
    private:
        double smoothing_parameter;
        std::vector<double> current_cycle;                       // Cycle fed to model for evaluation
        std::vector< std::vector<double> > modeled_cycles;       // Saving all modeled cycles
        std::vector< std::vector<double> > retrieved_time_steps; // Saving time-steps of signal for later use
        int cycle_number;


    public:
        /*
        Constructor for initializing model with smooth parameter
        */
        AverageDiscretizedModel(double value);          
        
        double evaluateBackground(int i) const override;

        void addCycle(TimeSeriesData sampleData) override;
        

        /*
        Function to update and save modeled background signal
        */
        void update_background_cycle(int i);

        int return_cycle_number();

        TimeSeriesData createData(int nCycles) override;
    

};


#endif