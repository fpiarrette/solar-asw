
#ifndef TASK_TO_MODEM_H
#define TASK_TO_MODEM_H

#include "Channel.h"
#include "CircularBuffer.h"
#include "Scheduller.h"

class TaskToModem : public Scheduller::Task
{
public:
    ~TaskToModem()
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

protected:
private:
    Channel *source;
    Channel *sink;
    CircularBuffer storage;
    char bufferRx[512];
    int bufferRxSize;
};

#endif
