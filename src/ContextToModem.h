#include "Context.h"

#include "ChannelSocketServer.h"
#include "ChannelSpi.h"

#ifndef CONTEXT_TO_MODEM_H
#define CONTEXT_TO_MODEM_H

class ContextToModem : public Context
{
public:
    Channel *getSource(void);
    Channel *getSink(void);
    ChannelSocketServer *getChannelSocketServer(void);

protected:
    ChannelSocketServer channelSocketServer;
    ChannelSpi channelSpi;

private:
};

#endif
