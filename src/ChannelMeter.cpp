#include "ChannelMeter.h"

ChannelMeter::ChannelMeter(Channel &target)
    : target_(target)
{
}

Channel::Error ChannelMeter::start(void)
{
    return target_.start();
}

Channel::Error ChannelMeter::tx(Fifo<char> &f)
{
    size_t b = f.size();
    Channel::Error r = target_.tx(f);
    size_t a = f.size();
    meterTx.addDiff(b - a);
    return r;
}

Channel::Error ChannelMeter::rx(Fifo<char> &f)
{
    size_t b = f.size();
    Channel::Error r = target_.rx(f);
    size_t a = f.size();
    meterRx.addDiff(b - a);
    return r;
}

Channel::Error ChannelMeter::stop(void)
{
    return target_.stop();
}

Meter *ChannelMeter::getMeterRx(void)
{
    return &meterRx;
}

Meter *ChannelMeter::getMeterTx(void)
{
    return &meterTx;
}