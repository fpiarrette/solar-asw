
#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>

class Signals
{
public:
    void init(void);
    static Signals *getInstance(void);
    int isStopped(void);
    int isTerminated(void);
    static void handler(int signal);

protected:
    Signals();
private:
    static Signals instance;

    volatile sig_atomic_t stopped;
    volatile sig_atomic_t terminated;
};

#endif
