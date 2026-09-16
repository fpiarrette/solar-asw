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
}

void Platform::shutdown(void)
{
    /* really not needed to free Gpio as it is mocked */
}

Gpio *Platform::getGpio(void)
{
    return &gpio;
}
