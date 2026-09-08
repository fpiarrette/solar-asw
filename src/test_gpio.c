#include "Logger.h"

#include "Gpio.h"

int main(int argc, char *argv[])
{
    Logger::config(Logger::Type::STDOUT);

    Logger::getInstance()->setLevel(1);
    Logger::getInstance()->start("Channel SPI test");

    L_INFO("Starting...");

    int line, value;
    GpioAbstract::Error result;

    Gpio::configure(Gpio::Type::MODULE);

    line = 1;

    Gpio::getInstance()->configure(line, GpioAbstract::Type::IN);

    result = Gpio::getInstance()->get(line, &value);

    L_DEBUG("line %d value %d with result %d", line, value, result);

    Gpio::getInstance()->stop();

    L_INFO("Finishing...");

    Logger::getInstance()->stop();

    return EXIT_SUCCESS;
}
