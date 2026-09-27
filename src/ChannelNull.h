#include "Channel.h"

#ifndef CHANNEL_NULL_H
#define CHANNEL_NULL_H

class ChannelNull : public Channel
{
public:
    ~ChannelNull()
    {
        /* make sure that stop function is called */
        stop();
    }
    Channel::Error start(void);
    Channel::Error tx(Fifo<char> &f);
    Channel::Error rx(Fifo<char> &f);
    Channel::Error stop(void);

protected:
private:
};

#endif
