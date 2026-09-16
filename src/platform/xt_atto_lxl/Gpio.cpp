#include "Gpio.h"

#include "Logger.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

#define LOG_PREFIX "GPIO module "

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

    if (fdChip < 0)
    {

        fdChip = open(deviceName, O_RDWR);

        if (fdChip < 0)
        {
            LOGGER_DEBUG_ERRNO;

            L_ERROR("error openning gpio");

            return Gpio::Error::E_INT;
        }

        return Gpio::Error::E_OK;
    }
    else
    {
        return Gpio::Error::E_STA;
    }
}

Gpio::Error Gpio::configure(int _port, int _line, Type _type)
{
    struct gpiohandle_request request;

    if (fdChip < 0)
    {
        L_WARNING(LOG_PREFIX "wrong state");

        return Gpio::Error::E_STA;
    }

    L_DEBUG("configuring port %d, ine %d as %s", _port, _line, _type == Gpio::Type::IN ? "IN" : "OUT");

    if (_port < 0 || _port >= GPIO_NUM_PORTS)
    {
        return Gpio::Error::E_ARG;
    }

    if (_line < 0 || _line >= GPIO_NUM_LINES)
    {
        return Gpio::Error::E_ARG;
    }

    if (port[_port].line[_line] < 0)
    {
        memset(&request, 0, sizeof(request));

        request.lineoffsets[0] = _port * _line;
        request.lines = 1;

        if (_type == Gpio::Type::OUT)
            request.flags = GPIOHANDLE_REQUEST_OUTPUT;
        else if (_type == Gpio::Type::IN)
            request.flags = GPIOHANDLE_REQUEST_INPUT;
        else
            return Gpio::Error::E_INT;

        if (ioctl(fdChip, GPIO_GET_LINEHANDLE_IOCTL, &request) < 0)
        {
            LOGGER_DEBUG_ERRNO;

            L_ERROR("requesting GPIO control to kernel");

            return Gpio::Error::E_INT;
        }

        /* store line file descriptor */
        port[_port].line[_line] = request.fd;

        return Gpio::Error::E_OK;
    }
    else
    {
        return Gpio::Error::E_STA;
    }
}

Gpio::Error Gpio::get(int _port, int _line, int *v)
{
    struct gpiohandle_data data;

    if (_port < 0 || _port >= GPIO_NUM_PORTS)
    {
        return Gpio::Error::E_ARG;
    }

    if (_line < 0 || _line >= GPIO_NUM_LINES)
    {
        return Gpio::Error::E_ARG;
    }

    if (port[_port].line[_line] < 0)
    {
        /* line was not configured */
        return Gpio::Error::E_STA;
    }

    memset(&data, 0, sizeof(data));

    if (ioctl(port[_port].line[_line], GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data) < 0)
    {
        LOGGER_DEBUG_ERRNO;

        return Gpio::Error::E_INT;
    }

    L_DEBUG("Port %d, line %d is %d", _port, _line, data.values[0]);

    /* assign result */
    *v = data.values[0];

    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::set(int _port, int _line, int v)
{
    struct gpiohandle_data data;

    L_DEBUG("setting port %d, line %d to value %d", _port, _line, v);

    if (_port < 0 || _port >= GPIO_NUM_PORTS)
    {
        return Gpio::Error::E_ARG;
    }

    if (_line < 0 || _line >= GPIO_NUM_LINES)
    {
        return Gpio::Error::E_ARG;
    }

    if (port[_port].line[_line] < 0)
    {
        /* line was not configured */
        return Gpio::Error::E_STA;
    }

    memset(&data, 0, sizeof(data));

    data.values[0] = (v != 0) ? 1 : 0;

    if (ioctl(port[_port].line[_line], GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) < 0)
    {
        LOGGER_DEBUG_ERRNO;

        L_ERROR("setting GPIO line value");
    }

    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::stop(void)
{
    for (int i = 0; i < GPIO_NUM_PORTS; i++)
        for (int j = 0; j < GPIO_NUM_LINES; j++)
        {
            if (port[i].line[j] > 0)
            {
                if (close(port[i].line[j]) < 0)

                    LOGGER_DEBUG_ERRNO;

                port[i].line[j] = -1;
            }
        }

    if (fdChip > 0)
    {
        if (close(fdChip) < 0)

            LOGGER_DEBUG_ERRNO;

        fdChip = -1;
    }

    L_NOTICE(LOG_PREFIX "stopped");

    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::setDeviceName(const char *name)
{
    strncpy(deviceName, name, GPIO_DEV_NAME_SIZE);

    if (strcmp(deviceName, name) == 0)
        return Gpio::Error::E_OK;
    else
        return Gpio::Error::E_ARG;
}
