#include "Platform.h"

#include "Gpio.h"
#include "Logger.h"

#define LOG_PREFIX "Platform host "

Platform Platform::instance;

Platform *Platform::getInstance(void)
{
    return &instance;
}

Platform::Platform(void)
{
}

void Platform::init(void)
{
    Gpio::configure(Gpio::Type::MOCK);

    /* Line 0 as input is just an example */
    Gpio::getInstance()->configure(0, GpioAbstract::Type::IN);
}

void Platform::shutdown(void)
{
    /* really not needed to free Gpio as it is mocked */
    Gpio::getInstance()->stop();
}
