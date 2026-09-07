
#ifndef TASK_KILLER_H
#define TASK_KILLER_H

#include "Channel.h"
#include "Scheduller.h"

class TaskKiller : public Scheduller::Task
{
public:
    ~TaskKiller()
    {
        stop();
    }
    const char *getName(void);
    void prepare(void);
    Scheduller::Task::Result run(long int time);
    void stop(void);

    void setSource(Channel *source);
    void setScheduller(Scheduller *s) { scheduller = s; }

protected:
private:
    Scheduller *scheduller;
    Channel *source;
};

#endif
