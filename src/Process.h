#include "ChannelSpi.h"
#include "ChannelSocketClient.h"
#include "ChannelSocketServer.h"

#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    void execute(void);

protected:
    virtual void init(void) = 0;
    virtual void run(long int time) = 0;
    virtual void start(void) = 0;
    virtual void stop(void) = 0;

    ChannelSocketClient channelSocketClient;
    ChannelSocketServer channelSocketServer;
    ChannelSpi channelSpi;
};

#endif
