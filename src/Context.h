#include "Channel.h"

#ifndef CONTEXT_H
#define CONTEXT_H

class Context
{
public:
    virtual Channel *getSource(void) = 0;
    virtual Channel *getSink(void) = 0;
};

#endif
