#include "Process.h"

#ifndef PROCESS_FROM_MODEM_H
#define PROCESS_FROM_MODEM_H

#define PROCESS_FROM_MODEM_LIMIT (512)

class ProcessFromModem : public Process
{
public:
    void start(void);
    void run(void);

private:
    char buffer[8 * 1024];
    int write;
};

#endif
