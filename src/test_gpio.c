#include "Logger.h"

#include "Gpio.h"

#include <stdio.h>
#include <stdlib.h>

void get_line_value(Gpio *gpio, char *deviceName, char *port, char *line)
{
    int p, l, v;
    Gpio::Error result;

    result = gpio->start();
    if (result != Gpio::Error::E_OK)
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

    result = gpio->configure(p, l, Gpio::Type::IN);

    if (result != Gpio::Error::E_OK)
    {
        L_ERROR("port %d, line %d can not be configured as input", p, l);
        return;
    }

    result = gpio->get(p, l, &v);

    if (result != Gpio::Error::E_OK)
    {
        L_ERROR("error reading port %d, line %d", p, l);
        return;
    }

    L_NOTICE("port %d, line %d is %s", p, l, v == 0 ? "off" : "on");

    result = gpio->stop();
    if (result != Gpio::Error::E_OK)
    {
        L_ERROR("stopping GPIO");
        return;
    }
}

void set_line_value(Gpio *gpio, char *deviceName, char *port, char *line, char *value)
{
    int p, l, v;
    Gpio::Error result;

    result = gpio->start();

    if (result != Gpio::Error::E_OK)
    {
        L_ERROR("starting GPIO");
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

    result = gpio->configure(p, l, Gpio::Type::OUT);

    if (result != Gpio::Error::E_OK)
    {
        L_ERROR("port %d, line %d can not be configured as output", p, l);
        return;
    }

    result = gpio->set(p, l, v);

    if (result != Gpio::Error::E_OK)
    {
        L_ERROR("error writing port %d, line %d", p, l);
        return;
    }

    L_NOTICE("port %d, line %d set to %d", p, l, v);

    L_INFO("Press any key to finish");

    getchar();

    result = gpio->stop();

    if (result != Gpio::Error::E_OK)
    {
        L_ERROR("stopping GPIO");
        return;
    }
}

int main(int argc, char *argv[])
{
    Gpio gpio;

    Logger::config(Logger::Type::STDOUT);

    Logger::getInstance()->setLevel(1);
    Logger::getInstance()->start("Channel SPI test");

    L_INFO("Starting...");

    switch (argc)
    {
    case 4:
    case 5:
        gpio.setDeviceName(argv[1]);

        if (argc == 4)
            get_line_value(&gpio, argv[1], argv[2], argv[3]);
        else
            set_line_value(&gpio, argv[1], argv[2], argv[3], argv[4]);

        break;

    default:
        L_ERROR("Wrong number of arguments");
        L_NOTICE("3 arguments: <device> <port> <line>");
        L_NOTICE("4 arguments: <device> <port> <line> <value>");

        break;
    }

    L_INFO("Finishing...");

    Logger::getInstance()->stop();

    return EXIT_SUCCESS;
}
