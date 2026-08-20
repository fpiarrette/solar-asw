#include "ChannelSpi.h"

Channel::Error ChannelSpi::init(void)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::start(void)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::tx(char *data, int size)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::rx(char *data, int size, int *received)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::stop(void)
{
    return Channel::Error::E_OK;
}
