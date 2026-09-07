#include "Signals.h"

#include "alarm_def.h"
#include "Alarms.h"
#include "Logger.h"

#define LOG_PREFIX "Signals "

Signals Signals::instance;

Signals *Signals::getInstance(void)
{
    return &instance;
}

Signals::Signals(void)
{
}

void Signals::init(void)
{
    struct sigaction s;
    s.sa_handler = handler;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTSTP, &s, NULL);
    sigaction(SIGCONT, &s, NULL);

    L_NOTICE(LOG_PREFIX "configured");
}

void Signals::handler(int signal)
{
    switch (signal)
    {
    case SIGINT:
        Signals::getInstance()->terminated = 1;
        Alarms::getInstance()->set(ALARM_DEF_KILL);
        break;
    case SIGTSTP:
        Signals::getInstance()->stopped = 1;
        Alarms::getInstance()->set(ALARM_DEF_STOP);
        break;
    case SIGCONT:
        Signals::getInstance()->stopped = 0;
        Alarms::getInstance()->set(ALARM_DEF_RESUME);
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
