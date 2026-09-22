
#ifndef PLATFORM_H
#define PLATFORM_H

#include "Gpio.h"

#ifdef DEBUG
#define BUILD_TYPE "Debug version"
#else
#define BUILD_TYPE "Release version"
#endif

class Platform
{
public:
    static Platform *getInstance(void);
    void init(void);
    void shutdown(void);
    Gpio *getGpio(void);
    const char *getName(void);

protected:
    Platform();

private:
    static Platform instance;
    Gpio gpio;
};

#endif
