#include "ChannelSpi.h"

#include "Logger.h"

#define LOG_PREFIX "Channel SPI "

Channel::Error ChannelSpi::init(void)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::start(void)
{
    L_NOTICE(LOG_PREFIX "started");

    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::tx(char *data, int size, int *tranmitted)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::rx(char *data, int size, int *received)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::stop(void)
{
    L_NOTICE(LOG_PREFIX "stopped");

    return Channel::Error::E_OK;
}
