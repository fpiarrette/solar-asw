#include "ChannelSpi.h"
#include "ChannelSocket.h"

#ifndef PROCESS_H
#define PROCESS_H

class Process
{
protected:
    ChannelSocket channelSocket;
    ChannelSpi channelSpi;

    virtual void start(void);
    virtual void stop(void);

public:
    virtual void init(void);
    void execute(void);

protected:
    virtual void run(long int time) = 0;
};

#endif
