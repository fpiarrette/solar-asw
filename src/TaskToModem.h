
#ifndef TASK_TO_MODEM_H
#define TASK_TO_MODEM_H

#include "Channel.h"
#include "Fifo.h"
#include "Scheduller.h"

class TaskToModem : public Scheduller::Task
{
public:
    TaskToModem(Channel &source_, Channel &sink_)
        : source(source_), sink(sink_), fifo(2 * 1024)
    {
    }

    ~TaskToModem()
    {
        stop();
    }
    const char *getName(void);
    void prepare(void);
    Scheduller::Task::Result run(long int time);
    void stop(void);

protected:
private:
    Channel &source;
    Channel &sink;
    Fifo<char> fifo;
};

#endif
