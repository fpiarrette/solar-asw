#include "Gpio.h"

#include "Logger.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

GpioAbstract *Gpio::instance;
GpioMock Gpio::gpioMock;
GpioModule Gpio::gpioModule;

GpioAbstract *Gpio::getInstance(void)
{
    return instance;
}

Gpio::Gpio()
{
}

void Gpio::configure(Gpio::Type type)
{
    if (instance != NULL)
    {
        return;
    }

    switch (type)
    {
    case Gpio::Type::MOCK:
        instance = &gpioMock;
        break;
    case Gpio::Type::MODULE:
        instance = &gpioModule;
        break;
    }
}
