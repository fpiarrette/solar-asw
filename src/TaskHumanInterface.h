
#ifndef TASK_HUMAN_INTERFACE_H
#define TASK_HUMAN_INTERFACE_H

#include "Scheduller.h"

class TaskHumanInterface : public Scheduller::Task
{
public:
    ~TaskHumanInterface()
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
};

#endif
