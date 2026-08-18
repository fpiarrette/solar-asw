#include "Channel.h"

#ifndef CHANNEL_SPI_H
#define CHANNEL_SPI_H

class ChannelSpi : public Channel
{
public:
    void init(void);
    void start(void);
    void send(char *data, int size);
    void receive(char *data, int size, int *received);
    void stop(void);
};

#endif
