#include "ChannelNull.h"

#include "Logger.h"

#define LOG_PREFIX "Null channel "

Channel::Error ChannelNull::init(void)
{
    L_NOTICE(LOG_PREFIX "init");
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::start(void)
{
    L_NOTICE(LOG_PREFIX "start");
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
    L_NOTICE(LOG_PREFIX "stop");
    return Channel::Error::E_OK;
}
