
#ifndef TASK_REST_H
#define TASK_REST_H

#include "Scheduller.h"

class TaskRest : public Scheduller::Task
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
