#include "ChannelSpi.h"
#include "ChannelSocket.h"

#ifndef PROCESS_H
#define PROCESS_H

class Process
{
protected:
    ChannelSocket channelSocket;
    ChannelSpi channelSpi;

    virtual void init(void);
    virtual void start(void);
    virtual void stop(void);

public:
    void execute(void);

protected:
    virtual void run(void) = 0;
};

#endif
