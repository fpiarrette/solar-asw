#include "GpioModule.h"

#include "Logger.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

#define LOG_PREFIX "GPIO module "

GpioModule::GpioModule()
{
    fdChip = -1;

    for (int n = 0; n < GPIO_NUM_LINES; n++)
    {
        fdLine[n] = -1;
    }

    memset(deviceName, 0, sizeof(deviceName));
}

GpioAbstract::Error GpioModule::start(void)
{
    L_NOTICE(LOG_PREFIX "starting");

    if (fdChip < 0)
    {

        fdChip = open(deviceName, O_RDWR);

        if (fdChip < 0)
        {
            LOGGER_DEBUG_ERRNO;

            L_ERROR("error openning gpio");

            return GpioAbstract::Error::E_INT;
        }

        return GpioAbstract::Error::E_OK;
    }
    else
    {
        return GpioAbstract::Error::E_STA;
    }
}

GpioAbstract::Error GpioModule::configure(int line, Type type)
{
    struct gpiohandle_request request;

    if (fdChip < 0)
    {
        L_WARNING(LOG_PREFIX "wrong state");

        return GpioAbstract::Error::E_STA;
    }

    L_DEBUG("configuring line %d as %s", line, type == GpioAbstract::Type::IN ? "IN" : "OUT");

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return GpioAbstract::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {

        memset(&request, 0, sizeof(request));

        request.lineoffsets[0] = line;
        request.lines = 1;

        if (type == GpioAbstract::Type::OUT)
            request.flags = GPIOHANDLE_REQUEST_OUTPUT;
        else if (type == GpioAbstract::Type::IN)
            request.flags = GPIOHANDLE_REQUEST_INPUT;
        else
            return GpioAbstract::Error::E_INT;

        if (ioctl(fdChip, GPIO_GET_LINEHANDLE_IOCTL, &request) < 0)
        {
            LOGGER_DEBUG_ERRNO;

            L_ERROR("requesting GPIO control to kernel");

            return GpioAbstract::Error::E_INT;
        }

        /* store line file descriptor */
        fdLine[line] = request.fd;

        return GpioAbstract::Error::E_OK;
    }
    else
    {
        return GpioAbstract::Error::E_STA;
    }
}

GpioAbstract::Error GpioModule::get(int line, int *v)
{
    struct gpiohandle_data data;

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return GpioAbstract::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {
        /* line was not configured */
        return GpioAbstract::Error::E_STA;
    }

    memset(&data, 0, sizeof(data));

    if (ioctl(fdLine[line], GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data) < 0)
    {
        LOGGER_DEBUG_ERRNO;

        return GpioAbstract::Error::E_INT;
    }

    L_DEBUG("Line %d is %d", line, data.values[0]);

    /* assign result */
    *v = data.values[0];

    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioModule::set(int line, int v)
{
    struct gpiohandle_data data;

    L_DEBUG("setting line %d to value %d", line, v);

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return GpioAbstract::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {
        /* line was not configured */
        return GpioAbstract::Error::E_STA;
    }

    memset(&data, 0, sizeof(data));

    data.values[0] = (v != 0) ? 1 : 0;

    if (ioctl(fdLine[line], GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) < 0)
    {
        LOGGER_DEBUG_ERRNO;

        L_ERROR("setting GPIO line value");
    }

    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioModule::stop(void)
{
    for (int n = 0; n < GPIO_NUM_LINES; n++)
    {
        if (fdLine[n] > 0)
        {
            if (close(fdLine[n]) < 0)

                LOGGER_DEBUG_ERRNO;

            fdLine[n] = -1;
        }
    }

    if (fdChip > 0)
    {
        if (close(fdChip) < 0)

            LOGGER_DEBUG_ERRNO;

        fdChip = -1;
    }

    L_NOTICE(LOG_PREFIX "stopped");

    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioModule::setDeviceName(const char *name)
{
    strncpy(deviceName, name, GPIO_DEV_NAME_SIZE);

    if (strcmp(deviceName, name) == 0)
        return GpioAbstract::Error::E_OK;
    else
        return GpioAbstract::Error::E_ARG;
}
