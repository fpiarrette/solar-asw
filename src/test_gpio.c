#include "Logger.h"

#include "Gpio.h"

#include <stdio.h>
#include <stdlib.h>

void getLineValue(char *deviceName, char *port, char *line)
{
    int p, l, v;
    GpioAbstract::Error result;

    result = Gpio::getInstance()->start();
    if (result != GpioAbstract::Error::E_OK)
    {
        L_ERROR("opening GPIO");
        return;
    }

    if (sscanf(port, "%d", &p) != 1)
    {
        L_ERROR("%s can not be converted to int", port);
        return;
    }

    if (sscanf(line, "%d", &l) != 1)
    {
        L_ERROR("%s can not be converted to int", line);
        return;
    }

    result = Gpio::getInstance()->configure(p, l, GpioAbstract::Type::IN);

    if (result != GpioAbstract::Error::E_OK)
    {
        L_ERROR("port %d, line %d can not be configured as input", p, l);
        return;
    }

    result = Gpio::getInstance()->get(p, l, &v);

    if (result != GpioAbstract::Error::E_OK)
    {
        L_ERROR("error reading port %d, line %d", p, l);
        return;
    }

    L_NOTICE("port %d, line %d is %s", l, v == 0 ? "off" : "on");

    result = Gpio::getInstance()->stop();
    if (result != GpioAbstract::Error::E_OK)
    {
        L_ERROR("stopping GPIO");
        return;
    }
}

void setLineValue(char *deviceName, char *port, char *line, char *value)
{
    int p, l, v;
    GpioAbstract::Error result;

    result = Gpio::getInstance()->start();
    if (result != GpioAbstract::Error::E_OK)
    {
        L_ERROR("opening GPIO");
        return;
    }

    if (sscanf(port, "%d", &p) != 1)
    {
        L_ERROR("%s can not be converted to int", port);
        return;
    }

    if (sscanf(line, "%d", &l) != 1)
    {
        L_ERROR("%s can not be converted to int", line);
        return;
    }

    if (sscanf(value, "%d", &v) != 1)
    {
        L_ERROR("%s can not be converted to int", value);
        return;
    }

    result = Gpio::getInstance()->configure(p, l, GpioAbstract::Type::OUT);

    if (result != GpioAbstract::Error::E_OK)
    {
        L_ERROR("port %d, line %d can not be configured as output", p, l);
        return;
    }

    result = Gpio::getInstance()->set(p, l, v);

    if (result != GpioAbstract::Error::E_OK)
    {
        L_ERROR("error writing port %d, line %d", p, l);
        return;
    }

    L_NOTICE("port %d, line %d set to %d", p, l, v);

    result = Gpio::getInstance()->stop();
    if (result != GpioAbstract::Error::E_OK)
    {
        L_ERROR("stopping GPIO");
        return;
    }
}

int main(int argc, char *argv[])
{
    Logger::config(Logger::Type::STDOUT);

    Logger::getInstance()->setLevel(1);
    Logger::getInstance()->start("Channel SPI test");

    L_INFO("Starting...");

    switch (argc)
    {
    case 4:
    case 5:
        Gpio::configure(Gpio::Type::MODULE);
        Gpio::getInstance()->setDeviceName(argv[1]);

        if (argc == 4)
            getLineValue(argv[1], argv[2], argv[3]);
        else
            setLineValue(argv[1], argv[2], argv[3], argv[4]);

        break;

    default:
        L_ERROR("Wrong number of arguments");
        L_NOTICE("2 arguments: <device> <line>");
        L_NOTICE("3 arguments: <device> <line> <value>");

        break;
    }

    L_INFO("Finishing...");

    Logger::getInstance()->stop();

    return EXIT_SUCCESS;
}
