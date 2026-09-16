#include "Channel.h"

#ifndef CHANNEL_SPI_H
#define CHANNEL_SPI_H

class ChannelSpi : public Channel
{
public:
    void setDeviceName(const char *name);
    void setClockPolarity(unsigned char cp);
    void setClockPhase(unsigned char ch);
    void setBits(unsigned char b);
    void setSpeed(unsigned int s);

protected:
    int fd;
    char deviceName[256];
    unsigned char clockPolarity;
    unsigned char clockPhase;
    unsigned char bits;
    unsigned int speed;

private:
};

#endif
