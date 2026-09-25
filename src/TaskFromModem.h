
#ifndef TASK_FROM_MODEM_H
#define TASK_FROM_MODEM_H

#include "Channel.h"
#include "Fifo.h"
#include "Scheduller.h"

class TaskFromModem : public Scheduller::Task
{
public:
    TaskFromModem()
        : fifo(2048)
    {
    }

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
    long int timeBarrier;
    int sizeLimit;
    int timeDeliveryLimit;
    Fifo<char> fifo;
};

#endif
