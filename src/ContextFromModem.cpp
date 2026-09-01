#include "ContextFromModem.h"

Channel *ContextFromModem::getSource(void)
{
    return &channelSpi;
}

Channel *ContextFromModem::getSink(void)
{
    return &channelSocketClient;
}

ChannelSocketClient *ContextFromModem::getChannelSocketClient(void)
{
    return &channelSocketClient;
}