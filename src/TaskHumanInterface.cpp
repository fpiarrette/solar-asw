#include "TaskHumanInterface.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"
#include "Gpio.h"
#include "gpio_def.h"

#define LOG_PREFIX "Human IFC task "

const char *TaskHumanInterface::getName(void)
{
    return "Human interface task";
}

void TaskHumanInterface::prepare(void)
{
    L_NOTICE(LOG_PREFIX "prepared");
}

int TaskHumanInterface::need(long int time)
{
    int needsToBeExecuted;
    needsToBeExecuted = Alarms::getInstance()->get(ALARM_DEF_ERROR) || Alarms::getInstance()->get(ALARM_DEF_WARNING);
    return needsToBeExecuted;
}

Scheduller::Task::Result TaskHumanInterface::run(long int time)
{
    if (!need(time))
        return Scheduller::Task::Result::IDLE;

    if (Alarms::getInstance()->get(ALARM_DEF_ERROR))
    {
        Gpio::getInstance()->set(GPIO_DEF_ERROR, 1);
    }

    if (Alarms::getInstance()->get(ALARM_DEF_WARNING))
    {
        Gpio::getInstance()->set(GPIO_DEF_WARNING, 1);
    }

    L_DEBUG("GPIO error notified");

    return Scheduller::Task::Result::WORKED;
}

void TaskHumanInterface::stop(void)
{
    L_NOTICE(LOG_PREFIX "stopped");
}
