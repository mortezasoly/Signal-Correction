#ifndef ABSTRACT_BACKGROUND_MODEL
#define ABSTRACT_BACKGROUND_MODEL

#include "TimeSeriesData.h"
class AbstractBackgroundModel 
{
    public:
        /**
        * returns the i-th sample of the modeled background signal 
        */
        virtual double evaluateBackground(int i) const = 0;
        /**
        * Refines the model using a new cycle of the background signal
        *  sampleData a time series representing one new cycle of a signal 
        */
        virtual void addCycle(TimeSeriesData sampleData) = 0;
        
        virtual TimeSeriesData createData(int nCycles) = 0;
};
#endif