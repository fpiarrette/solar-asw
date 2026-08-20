#include "Context.h"

#include "ChannelSocketClient.h"
#include "ChannelSpi.h"

#ifndef CONTEXT_FROM_MODEM_H
#define CONTEXT_FROM_MODEM_H

class ContextFromModem : public Context
{
public:
    Channel *getSource(void);
    Channel *getSink(void);

protected:
    ChannelSocketClient channelSocketClient;
    ChannelSpi channelSpi;

private:
};

#endif
