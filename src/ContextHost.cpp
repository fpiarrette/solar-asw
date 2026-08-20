#include "ContextHost.h"

Channel *ContextHost::getSource(void)
{
    return &channelSocketServer;
}

Channel *ContextHost::getSink(void)
{
    return &channelSocketClient;
}
