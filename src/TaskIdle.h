
#ifndef TASK_IDLE_H
#define TASK_IDLE_H

#include "Scheduller.h"

class TaskIdle : public Scheduller::Task
{
public:
    ~TaskIdle()
    {
        stop();
    }
    const char *getName(void);
    void prepare(void);
    int need(long int time);
    void run(long int time);
    void stop(void);

    void setScheduller(Scheduller *s) { scheduller = s; }

protected:
private:
    Scheduller *scheduller;
};

#endif
