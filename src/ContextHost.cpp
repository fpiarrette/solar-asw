#include "ContextHost.h"

Channel *ContextHost::getSource(void)
{
    return &channelSocketServer;
}

Channel *ContextHost::getSink(void)
{
    return &channelSocketClient;
}

ChannelSocketServer *ContextHost::getChannelSocketServer(void)
{
    return &channelSocketServer;
}

ChannelSocketClient *ContextHost::getChannelSocketClient(void)
{
    return &channelSocketClient;
}
