#include "Process.h"

#ifndef PROCESS_TO_MODEM_H
#define PROCESS_TO_MODEM_H

class ProcessToModem : public Process
{
public:
    void init(Context *context);
    void start(Context *context);
    void run(Context *context, long int time);
    void stop(Context *context);

protected:
private:
};

#endif
