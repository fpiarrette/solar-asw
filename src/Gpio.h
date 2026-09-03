
#ifndef GPIO_H
#define GPIO_H

#include "GpioAbstract.h"
#include "GpioMock.h"
#include "GpioModule.h"

class Gpio
{
public:
    enum Type
    {
        MOCK = 0,
        MODULE = 1,
    };

    static GpioAbstract *getInstance(void);
    static void configure(Gpio::Type type);

protected:
    Gpio();

private:
    static GpioAbstract *instance;
    static GpioMock gpioMock;
    static GpioModule gpioModule;
};

#endif
