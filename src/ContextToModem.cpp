#include "ContextToModem.h"

Channel *ContextToModem::getSource(void)
{
    return &channelSocketServer;
}

Channel *ContextToModem::getSink(void)
{
    return &channelSpi;
}
