
#ifndef METER_H
#define METER_H

#include <stdlib.h>

class Meter
{
public:
    Meter()
    {
        accumulated = 0;
        differencital = 0;
    }

    void processDifferential(void)
    {
        accumulated += differencital;
        differencital = 0;
    }

    size_t getDifferential(void)
    {
        return differencital;
    }

    size_t getAccumulated(void)
    {
        processDifferential();
        return accumulated;
    }

    void addDiff(size_t i)
    {
        differencital += i;
    }

protected:
private:
    size_t accumulated;
    size_t differencital;
};

#endif
