#include "Gpio.h"

#include "Logger.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

Gpio Gpio::instance;

Gpio *Gpio::getInstance(void)
{
    return &instance;
}

Gpio::Gpio()
{
    fdChip = -1;

    for (int n = 0; n < GPIO_NUM_LINES; n++)
    {
        fdLine[n] = -1;
    }

    memset(deviceName, 0, sizeof(deviceName));
}

Gpio::Error Gpio::start(void)
{
    if (fdChip < 0)
    {

        fdChip = open(deviceName, O_RDWR);

        if (fdChip < 0)
        {
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

Gpio::Error Gpio::configure(int line, Type type)
{
    struct gpio_v2_line_request request;

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return Gpio::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {

        memset(&request, 0, sizeof(request));

        request.num_lines = 1;
        request.offsets[0] = line;

        if (type == Gpio::Type::OUT)
            request.config.flags = GPIO_V2_LINE_FLAG_OUTPUT;
        else if (type == Gpio::Type::IN)
            request.config.flags = GPIO_V2_LINE_FLAG_INPUT;
        else
            return Gpio::Error::E_INT;

        if (ioctl(fdChip, GPIO_V2_GET_LINE_IOCTL, &request) < 0)
        {
            L_ERROR("requesting GPIO control to kernel");

            return Gpio::Error::E_INT;
        }

        /* store line file descriptor */
        fdLine[line] = request.fd;

        return Gpio::Error::E_OK;
    }
    else
    {
        return Gpio::Error::E_STA;
    }
}

Gpio::Error Gpio::get(int line, int *v)
{
    struct gpio_v2_line_values values;

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return Gpio::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {
        /* line was not configured */
        return Gpio::Error::E_STA;
    }

    memset(&values, 0, sizeof(values));

    values.mask = 1;

    if (ioctl(fdLine[line], GPIO_V2_LINE_GET_VALUES_IOCTL, &values) < 0)
    {
        return Gpio::Error::E_INT;
    }

    /* assign result */
    *v = (values.bits & 1);

    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::set(int line, int v)
{
    struct gpio_v2_line_values values;

    if (line < 0 || line >= GPIO_NUM_LINES)
    {
        return Gpio::Error::E_ARG;
    }

    if (fdLine[line] < 0)
    {
        /* line was not configured */
        return Gpio::Error::E_STA;
    }

    memset(&values, 0, sizeof(values));

    values.mask = 1;
    values.bits = v;

    if (ioctl(fdLine[line], GPIO_V2_LINE_SET_VALUES_IOCTL, &values) < 0)
    {
        L_ERROR("setting GPIO line value");
    }

    return Gpio::Error::E_OK;
}

Gpio::Error Gpio::stop(void)
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
