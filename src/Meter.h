
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

    size_t getDifferential(void)
    {
        accumulated += differencital;
        size_t d = differencital;
        differencital = 0;
        return d;
    }

    size_t getAccumulated(void)
    {
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
