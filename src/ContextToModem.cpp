#include "ContextToModem.h"

Channel *ContextToModem::getSource(void)
{
    return &channelSocketServer;
}

ChannelSocketServer *ContextToModem::getChannelSocketServer(void)
{
    return &channelSocketServer;
}

Channel *ContextToModem::getSink(void)
{
    return &channelSpi;
}
