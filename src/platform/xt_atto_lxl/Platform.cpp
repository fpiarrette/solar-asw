#include "Platform.h"

#include "Gpio.h"
#include "Logger.h"

#define LOG_PREFIX "Platform xt_atto_lxl"

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
    Gpio::configure(Gpio::Type::MODULE);

    /* Line 0 as input is just an example */
    Gpio::getInstance()->configure(0, GpioAbstract::Type::IN);
}

void Platform::init(void)
{
    /* configure all lines as input before stopping Gpio? */
    Gpio::getInstance()->configure(0, GpioAbstract::Type::IN);

    Gpio::getInstance()->stop();
}
