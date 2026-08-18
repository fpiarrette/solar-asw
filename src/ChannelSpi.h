#include "Channel.h"

#ifndef CHANNEL_SPI_H
#define CHANNEL_SPI_H

class ChannelSpi : public Channel
{
public:
    void init(void *data);
    void start(void *data);
    void send(char *data, int size);
    void receive(char *data, int *size);
    void stop(void *data);
};

#endif
