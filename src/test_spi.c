#include "Logger.h"

#include "ChannelSpi.h"

int main(int argc, char *argv[])
{
    Logger::config(Logger::Type::STDOUT);

    Logger::getInstance()->setLevel(1);
    Logger::getInstance()->start("Channel SPI test");

    L_INFO("Starting...");

    ChannelSpi channelSpi;

    channelSpi.setDeviceName("/dev/spidev0.0");

    channelSpi.init();
    channelSpi.start();

    char command[1] = {0x5a};
    int transmitted;
    int received;
    char receptionBuffer[256];
    Channel::Error result;

    result = channelSpi.tx(command, sizeof(command), &transmitted);

    L_DEBUG("Transmitted %d bytes, result %d", transmitted, result);

    result = channelSpi.rx(receptionBuffer, sizeof(receptionBuffer), &received);

    L_DEBUG("Rceived %d bytes, result %d", received, result);

    channelSpi.stop();

    L_INFO("Finishing...");

    Logger::getInstance()->stop();

    return EXIT_SUCCESS;
}
