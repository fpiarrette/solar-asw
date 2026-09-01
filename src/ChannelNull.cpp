#include "ChannelNull.h"

Channel::Error ChannelNull::init(void)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::start(void)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::tx(char *data, int size, int *transmitted)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::rx(char *data, int size, int *received)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::stop(void)
{
    return Channel::Error::E_OK;
}
