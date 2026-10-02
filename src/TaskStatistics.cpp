#include "TaskStatistics.h"

#include "Alarms.h"
#include "setup.h"
#include "Logger.h"

#define LOG_PREFIX "Statistics "

const char *TaskStatistics::getName(void)
{
    return "Statistics task";
}

void TaskStatistics::prepare(void)
{
    L_NOTICE(LOG_PREFIX "prepared");
}

int TaskStatistics::need(long int time)
{
    int needsToBeExecuted;
    /* every second */
    needsToBeExecuted = Alarms::getInstance()->get(SETUP_ALARM_SECOND);
    return needsToBeExecuted;
}

Scheduller::Task::Result TaskStatistics::run(long int time)
{
    Scheduller::Task::Result r;

    r = Scheduller::Task::Result::IDLE;

    if (Alarms::getInstance()->get(SETUP_ALARM_TENTH_SECOND))
    {
        /* Just print */
        L_DEBUG("From modem: %d", fromModem.getMeterRx()->getAccumulated());
        L_DEBUG("To modem: %d", toModem.getMeterRx()->getAccumulated());
    }

    if (Alarms::getInstance()->get(SETUP_ALARM_SECOND))
    {
        /* DO THE JOB!!!! */
        r = Scheduller::Task::Result::WORKED;
    }

#if 0
    size_t a;

    Alarms::getInstance()->set(SETUP_ALARM_TO_MODEM_METER_ACCUMULATED);
    a = toModem->getMeterRx()->getAccumulated();
    Alarms::getInstance()->setCookie(SETUP_ALARM_TO_MODEM_METER_ACCUMULATED, &a);

    Alarms::getInstance()->set(SETUP_ALARM_FROM_MODEM_METER_ACCUMULATED);
    a = fromModem->getMeterRx()->getAccumulated();
    Alarms::getInstance()->setCookie(SETUP_ALARM_FROM_MODEM_METER_ACCUMULATED, &a);

#endif

    return r;
}

void TaskStatistics::stop(void)
{
    L_NOTICE(LOG_PREFIX "stopped");
}
