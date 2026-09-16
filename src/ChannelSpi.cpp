#include "ChannelSpi.h"

#include <string.h>

void ChannelSpi::setDeviceName(const char *name)
{
    strncpy(deviceName, name, sizeof(deviceName));
}

void ChannelSpi::setClockPolarity(unsigned char cp)
{
    clockPolarity = cp;
}
void ChannelSpi::setClockPhase(unsigned char ch)
{
    clockPhase = ch;
}
void ChannelSpi::setBits(unsigned char b)
{
    bits = b;
}
void ChannelSpi::setSpeed(unsigned int s)
{
    speed = s;
}
