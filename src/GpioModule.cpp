#include "GpioModule.h"

#include "Logger.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

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
    if (fdChip < 0)
    {

        fdChip = open(deviceName, O_RDWR);

        if (fdChip < 0)
        {
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
    struct gpio_v2_line_request request;

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return GpioAbstract::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {

        memset(&request, 0, sizeof(request));

        request.num_lines = 1;
        request.offsets[0] = line;

        if (type == GpioAbstract::Type::OUT)
            request.config.flags = GPIO_V2_LINE_FLAG_OUTPUT;
        else if (type == GpioAbstract::Type::IN)
            request.config.flags = GPIO_V2_LINE_FLAG_INPUT;
        else
            return GpioAbstract::Error::E_INT;

        if (ioctl(fdChip, GPIO_V2_GET_LINE_IOCTL, &request) < 0)
        {
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
    struct gpio_v2_line_values values;

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return GpioAbstract::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {
        /* line was not configured */
        return GpioAbstract::Error::E_STA;
    }

    memset(&values, 0, sizeof(values));

    values.mask = 1;

    if (ioctl(fdLine[line], GPIO_V2_LINE_GET_VALUES_IOCTL, &values) < 0)
    {
        return GpioAbstract::Error::E_INT;
    }

    /* assign result */
    *v = (values.bits & 1);

    return GpioAbstract::Error::E_OK;
}

GpioAbstract::Error GpioModule::set(int line, int v)
{
    struct gpio_v2_line_values values;

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return GpioAbstract::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {
        /* line was not configured */
        return GpioAbstract::Error::E_STA;
    }

    memset(&values, 0, sizeof(values));

    values.mask = 1;
    values.bits = v;

    if (ioctl(fdLine[line], GPIO_V2_LINE_SET_VALUES_IOCTL, &values) < 0)
    {
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
            close(fdLine[n]);
            fdLine[n] = -1;
        }
    }

    if (fdChip > 0)
    {
        close(fdChip);
        fdChip = -1;
    }

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
