
#ifndef PLATFORM_H
#define PLATFORM_H

#include "Gpio.h"

class Platform
{
public:
    static Platform *getInstance(void);
    void init(void);
    void shutdown(void);
    Gpio *getGpio(void);

protected:
    Platform();

private:
    static Platform instance;
    Gpio gpio;
};

#endif
