#include "ContextHost.h"

Channel *ContextHost::getSource(void)
{
    return &channelSocketServer;
    /* return &channelNull; */
}

Channel *ContextHost::getSink(void)
{
    return &channelSocketClient;
}
