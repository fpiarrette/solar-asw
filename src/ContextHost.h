#include "Context.h"

#include "ChannelSocketClient.h"
#include "ChannelSocketServer.h"

#ifndef CONTEXT_HOST_H
#define CONTEXT_HOST_H

class ContextHost : public Context
{
public:
    Channel *getSource(void);
    Channel *getSink(void);

protected:
    ChannelSocketClient channelSocketClient;
    ChannelSocketServer channelSocketServer;

private:
};

#endif
