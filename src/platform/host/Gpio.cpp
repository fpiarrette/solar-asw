#include "Gpio.h"

#include "Logger.h"

#define LOG_PREFIX "GPIO mock "

Gpio::Gpio()
{
    fdChip = -1;

    for (int i = 0; i < GPIO_NUM_PORTS; i++)
        for (int j = 0; j < GPIO_NUM_LINES; j++)
        {
            port[i].line[j] = -1;
        }

    memset(deviceName, 0, sizeof(deviceName));
}

Gpio::Error Gpio::start(void)
{
    L_NOTICE(LOG_PREFIX "starting");
    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::configure(int port, int line, Gpio::Type type)
{
    L_DEBUG("configuring port %d, line %d as %s", port, line, type == Gpio::Type::IN ? "IN" : "OUT");

    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::get(int port, int line, int *v)
{
    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::set(int port, int line, int v)
{
    L_DEBUG("setting line %d to value %d", line, v);

    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::stop(void)
{
    L_NOTICE(LOG_PREFIX "stopped");
    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::setDeviceName(const char *name)
{
    return Gpio::Error::E_OK;
}
