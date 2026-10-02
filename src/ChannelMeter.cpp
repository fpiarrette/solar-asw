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
    size_t before = f.size();
    Channel::Error r = target_.tx(f);
    size_t after = f.size();
    /* in case of transmition is expected that size after transmition were smaller than before */
    size_t d = before - after;
    if (d > 0)
        meterTx.addDiff(d);
    return r;
}

Channel::Error ChannelMeter::rx(Fifo<char> &f)
{
    size_t before = f.size();
    Channel::Error r = target_.rx(f);
    size_t after = f.size();
    /* in case of reception is expected that size after reception were bigger than before */
    size_t d = after - before;
    if (d > 0)
        meterRx.addDiff(d);
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