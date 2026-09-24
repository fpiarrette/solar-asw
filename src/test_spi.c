#include "Logger.h"

#include "ChannelSpiMaster.h"

#include "test_common.h"

#include <stdio.h>
#include <stdlib.h>

void send_n_receive(ChannelSpiMaster *spi, char *device_name, char *hex_string)
{
    char data_tx[256];
    int transmitted, size;
    char data_rx[256];
    int received;
    char converted_string[(sizeof(data_rx) * 2) + 1];
    Channel::Error result;

    spi->setDeviceName(device_name);

    result = spi->start();

    if (result != Channel::Error::E_OK)
    {
        L_ERROR("starting");
        return;
    }

    if (str_2_hex(data_tx, hex_string, &size) != 0)
    {
        L_ERROR("converting %s", hex_string);
        return;
    }

    result = spi->tx(data_tx, size, &transmitted);

    if (result != Channel::Error::E_OK)
    {
        L_ERROR("transmitting");
        return;
    }

    L_NOTICE("transmitted %d bytes, result %d", transmitted, result);

    result = spi->rx(data_rx, sizeof(data_rx), &received);

    if (result != Channel::Error::E_OK)
    {
        L_ERROR("receiving");
        return;
    }

    L_NOTICE("received %d bytes, result %d", received, result);

    hex_2_str(converted_string, data_rx, received);

    L_NOTICE("received data: %s", converted_string);
}

int main(int argc, char *argv[])
{
    Logger::config(Logger::Type::STDOUT);

    Logger::getInstance()->setLevel(1);
    Logger::getInstance()->start("Channel SPI test");

    L_INFO("Starting...");

    ChannelSpiMaster channelSpiMaster;

    switch (argc)
    {
    case 3:

        send_n_receive(&channelSpiMaster, argv[1], argv[2]);

        break;

    default:
        L_ERROR("Wrong number of arguments");
        L_NOTICE("2 arguments: <device> <hex message>");
        break;
    }

    L_INFO("Finishing...");

    Logger::getInstance()->stop();

    return EXIT_SUCCESS;
}
