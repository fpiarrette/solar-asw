
#ifndef TASK_HUMAN_INTERFACE_H
#define TASK_HUMAN_INTERFACE_H

#include "Scheduller.h"

class TaskHumanInterface : public Scheduller::Task
{
public:
    const char *getName(void);
    void prepare(void);
    int need(long int time);
    void run(long int time);
    void stop(void);

protected:
private:
};

#endif
