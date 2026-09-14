#include "Platform.h"

#include "Gpio.h"
#include "platform_def.h"
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

    Gpio::getInstance()->configure(PLATFORM_GPIO_PORT, PLATFORM_GPIO_LINE_ERROR, GpioAbstract::Type::OUT);
    Gpio::getInstance()->configure(PLATFORM_GPIO_PORT, PLATFORM_GPIO_LINE_WARNING, GpioAbstract::Type::OUT);
}

void Platform::shutdown(void)
{
    /* really not needed to free Gpio as it is mocked */
    Gpio::getInstance()->stop();
}
