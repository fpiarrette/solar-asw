#include "Process.h"

#ifndef PROCESS_TO_MODEM_H
#define PROCESS_TO_MODEM_H

class ProcessToModem : public Process
{
public:
    void init(void);
    void start(void);
    void run(long int time);
    void stop(void);
};

#endif
