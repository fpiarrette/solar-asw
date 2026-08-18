
#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    virtual void init(void) = 0;
    virtual void run(void) = 0;
};

#endif
