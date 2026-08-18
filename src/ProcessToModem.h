#include "Process.h"

#ifndef PROCESS_TO_MODEM_H
#define PROCESS_TO_MODEM_H

class ProcessToModem : public Process
{
public:
    void init(void);
    void run(void);
    void stop(void);
};

#endif
