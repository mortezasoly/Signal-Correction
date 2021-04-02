#ifndef Mock_Fitted_Background_Model
#define Mock_Fitted_Background_Model

#include "TimeSeriesData.h"
#include "AbstractBackgroundModel.h"
#include <cmath>
#include <iostream>


const int SAMPLES_PER_CYCLE = 200;
const int NUMBER_OF_CYCLES_MOCK = 50;

class MockFittedBackgroundModel : public AbstractBackgroundModel 
{ 
    private:
        const double A;
        const double f;
        const double offset;
        const double phase;
        std::vector<double> current_cycle;                      // current cycle of signal that loaded into model
        std::vector< std::vector<double> > modeled_cycles;      // for saving background model cycle by cycle
        std::vector< std::vector<double> > retrieved_time_steps;// for saving time-steps that can be later used
        int cycle_number;                                       // determines which cycle of data is currently loaded

    public:
        MockFittedBackgroundModel(
            double A = 0.05, double f = 1.0e3, double offset = 0.45, double phase = 5.0 );


        double evaluateBackground(int i) const override;
        
        void addCycle(TimeSeriesData sampleData) override;

        TimeSeriesData createData(int nCycles) override;

        /*
        returns cycle_number, can be used to find out the current cycle
        */
        int return_cycle_number();


        /* 
        This function used to update current background signal based on evaluate_background
        and save it in "modeled_cycles" for later use.
        */
        void update_background_cycle( int i );

    
};

#endif