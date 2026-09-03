#include "GpioMock.h"

#include "Logger.h"

#define LOG_PREFIX "GPIO mock "

GpioAbstract::Error GpioMock::start(void)
{
    L_NOTICE(LOG_PREFIX "starting");
    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::configure(int line, GpioAbstract::Type type)
{
    L_DEBUG("configuring line %d as %s", line, type == GpioAbstract::Type::IN? "IN" : "OUT");

    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::get(int line, int *v)
{
    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::set(int line, int v)
{
    L_DEBUG("setting line %d to value %d", line, v);

    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::stop(void)
{
    L_NOTICE(LOG_PREFIX "stopped");
    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::setDeviceName(const char *name)
{
    return GpioAbstract::Error::E_OK;
}
