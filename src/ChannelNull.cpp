#include "ChannelNull.h"

#include "Logger.h"

#define LOG_PREFIX "Null channel "

Channel::Error ChannelNull::start(void)
{
    L_NOTICE(LOG_PREFIX "start");
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::tx(Fifo<char> &f)
{
    L_DEBUG("tx: %d", f.size());
    /* simulate that data is transmitted */
    f.consume(f.size());
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::rx(Fifo<char> &f)
{
    /* simulate that there is not input data */
    return Channel::Error::E_OK;
}

Channel::Error ChannelNull::stop(void)
{
    L_NOTICE(LOG_PREFIX "stopped");
    return Channel::Error::E_OK;
}
