#include "Context.h"

#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    void execute(Context *context);

protected:
    virtual void init(Context *context) = 0;
    virtual void run(Context *context, long int time) = 0;
    virtual void start(Context *context) = 0;
    virtual void stop(Context *context) = 0;
};

#endif
