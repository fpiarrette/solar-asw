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
    Channel::Error init(void);
    Channel::Error start(void);
    Channel::Error tx(char *data, int size, int *transmitted);
    Channel::Error rx(char *data, int size, int *received);
    Channel::Error stop(void);

protected:
private:
};

#endif
