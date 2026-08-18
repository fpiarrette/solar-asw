#include "ChannelSpi.h"
#include "ChannelSocket.h"

#ifndef PROCESS_H
#define PROCESS_H

class Process
{
protected:
    ChannelSocket channelSocket;
    ChannelSpi channelSpi;

public:
    void init(void);
    void start(void);
    void stop(void);

public:
    virtual void run(void) = 0;
};

#endif
