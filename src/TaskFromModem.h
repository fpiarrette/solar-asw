
#ifndef TASK_FROM_MODEM_H
#define TASK_FROM_MODEM_H

#include "Channel.h"
#include "CircularBuffer.h"
#include "Scheduller.h"

class TaskFromModem : public Scheduller::Task
{
public:
    ~TaskFromModem()
    {
        stop();
    }
    const char *getName(void);
    void prepare(void);
    int need(long int time);
    Scheduller::Task::Result run(long int time);
    void stop(void);

    void setSource(Channel *source);
    void setSink(Channel *sink);
    void setTimeDeliveryLimit(int value);
    void setSizeLimit(int value);

protected:
    void forwardToSink(long int time);

private:
    Channel *source;
    Channel *sink;
    char bufferRx[512];
    int bufferRxSize;
    long int timeBarrier;
    int sizeLimit;
    int timeDeliveryLimit;
    CircularBuffer bufferStorage;
};

#endif
