#include "GpioMock.h"

#include "Logger.h"

GpioAbstract::Error GpioMock::start(void)
{
    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::configure(int line, GpioAbstract::Type type)
{
    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::get(int line, int *v)
{
    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::set(int line, int v)
{
    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::stop(void)
{
    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioMock::setDeviceName(const char *name)
{
    return GpioAbstract::Error::E_OK;
}
