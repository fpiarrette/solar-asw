
#ifndef CHANNEL_METER_H
#define CHANNEL_METER_H

#include "Channel.h"
#include "Meter.h"

class ChannelMeter : public Channel
{
public:
    explicit ChannelMeter(Channel &target);

    Error start(void);
    Error tx(Fifo<char> &f);
    Error rx(Fifo<char> &f);
    Error stop(void);

    Meter *getMeterRx(void);
    Meter *getMeterTx(void);

protected:
private:
    Channel &target_;
    Meter meterTx;
    Meter meterRx;
};

#endif
