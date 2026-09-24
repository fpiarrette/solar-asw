#include "Platform.h"

#include "Gpio.h"
#include "setup.h"
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
}

void Platform::shutdown(void)
{
    /* really not needed to free Gpio as it is mocked */
}

Gpio *Platform::getGpio(void)
{
    return &gpio;
}

const char *Platform::getName(void)
{
    return "Platform XT ATTO LXL (" BUILD_TYPE ")";
}
