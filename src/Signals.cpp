#include "Signals.h"

Signals Signals::instance;

Signals *Signals::getInstance(void)
{
    return &instance;
}

void Signals::init(void)
{
    struct sigaction s;
    s.sa_handler = handler;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTSTP, &s, NULL);
    sigaction(SIGCONT, &s, NULL);
}

void Signals::handler(int signal)
{
    switch (signal)
    {
    case SIGINT:
        Signals::getInstance()->terminated = 1;
        break;
    case SIGTSTP:
        Signals::getInstance()->stopped = 1;
        break;
    case SIGCONT:
        Signals::getInstance()->stopped = 0;
        break;
    default:
        break;
    }
}

int Signals::isStopped(void)
{
    return stopped;
}

int Signals::isTerminated(void)
{
    return terminated;
}
