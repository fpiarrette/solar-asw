
#ifndef TASK_STATISTICS_H
#define TASK_STATISTICS_H

#include "Scheduller.h"

#include "ChannelMeter.h"

class TaskStatistics : public Scheduller::Task
{
public:
    TaskStatistics(ChannelMeter &toModem_, ChannelMeter &fromModem_)
        : toModem(toModem_), fromModem(fromModem_)
    {
    }
    ~TaskStatistics()
    {
        stop();
    }
    const char *getName(void);
    void prepare(void);
    int need(long int time);
    Scheduller::Task::Result run(long int time);
    void stop(void);

protected:
private:
    ChannelMeter &toModem;
    ChannelMeter &fromModem;
};

#endif
