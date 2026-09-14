#include "Logger.h"

#include "ChannelSpi.h"

#include <stdio.h>
#include <stdlib.h>

int fromStringToHex(char *hex, char *str, int *size)
{
    char b[3];
    int v, l, s, n;

    l = strlen(str);

    if ((l % 1) != 0)
    {
        L_ERROR("invalid hex string length");
        return -1;
    }

    s = 0;

    for (n = 0; n < l; n += 2, s++)
    {
        b[0] = str[n + 0];
        b[1] = str[n + 1];
        b[2] = 0;

        if (sscanf(b, "%d", &v) != 1)
        {
            L_ERROR("invalid hex string content: %s", b);
            return -2;
        }

        hex[s] = v;
    }

    *size = s;

    return 0;
}

int fromHexToString(char *str, char *hex, int size)
{
    int n;

    for (n = 0; n < size; n++)
    {
        sprintf(&str[n * 2], "%02d", hex[n]);
    }

    str[n * 2] = 0;

    return 0;
}

void sendAndReceive(ChannelSpi *spi, char *device_name, char *hex_string)
{
    char data_tx[256];
    int transmitted, size;
    char data_rx[256];
    int received;
    char converted_string[(sizeof(data_rx) * 2) + 1];
    Channel::Error result;

    spi->setDeviceName(device_name);

    result = spi->init();

    if (result != Channel::Error::E_OK)
    {
        L_ERROR("initialization");
        return;
    }

    result = spi->start();

    if (result != Channel::Error::E_OK)
    {
        L_ERROR("starting");
        return;
    }

    if (fromStringToHex(data_tx, hex_string, &size) != 0)
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

    fromHexToString(converted_string, data_rx, received);

    L_NOTICE("received data: %s", converted_string);
}

int main(int argc, char *argv[])
{
    Logger::config(Logger::Type::STDOUT);

    Logger::getInstance()->setLevel(1);
    Logger::getInstance()->start("Channel SPI test");

    L_INFO("Starting...");

    ChannelSpi channelSpi;

    switch (argc)
    {
    case 3:

        sendAndReceive(&channelSpi, argv[1], argv[2]);

        channelSpi.stop();

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
