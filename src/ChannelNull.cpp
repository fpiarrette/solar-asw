#include "ChannelNull.h"

#include "Logger.h"

Channel::Error ChannelNull::init(void)
{
    L_DEBUG("init");
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::start(void)
{
    L_DEBUG("start");
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::tx(char *data, int size, int *transmitted)
{
    L_DEBUG("tx: %d", size);
    /* simulate that data is transmitted */
    *transmitted = size;
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::rx(char *data, int size, int *received)
{
    /* simulate that there is not input data */
    *received = 0;
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::stop(void)
{
    L_DEBUG("stop");
    return Channel::Error::E_OK;
}
