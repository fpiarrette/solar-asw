#include "TaskHumanInterface.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"
#include "Platform.h"
#include "setup.h"

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
        Platform::getInstance()->getGpio()->set(SETUP_GPIO_ERROR_PORT, SETUP_GPIO_ERROR_LINE, 1);
    }

    if (Alarms::getInstance()->get(ALARM_DEF_WARNING))
    {
        Platform::getInstance()->getGpio()->set(SETUP_GPIO_WARNING_PORT, SETUP_GPIO_WARNING_LINE, 1);
    }

    L_DEBUG("GPIO error notified");

    return Scheduller::Task::Result::WORKED;
}

void TaskHumanInterface::stop(void)
{
    L_NOTICE(LOG_PREFIX "stopped");
}
