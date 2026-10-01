
#ifndef TASK_STATISTICS_H
#define TASK_STATISTICS_H

#include "Scheduller.h"

#include "ChannelMeter.h"

class TaskStatistics : public Scheduller::Task
{
public:
    ~TaskStatistics()
    {
        stop();
    }
    const char *getName(void);
    void prepare(void);
    int need(long int time);
    Scheduller::Task::Result run(long int time);
    void stop(void);

    void setToModem(ChannelMeter *c);
    void setFromModem(ChannelMeter *c);

protected:
private:
    ChannelMeter *toModem;
    ChannelMeter *fromModem;
};

#endif
