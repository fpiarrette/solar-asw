#include "Alarms.h"

#include "Logger.h"

#include <string.h>

Alarms Alarms::instance;

Alarms *Alarms::getInstance(void)
{
    return &instance;
}

int Alarms::get(int alarmId)
{
    return alarms[alarmId];
}

void Alarms::set(int alarmId)
{
    alarms[alarmId] = 1;
}

void Alarms::clear(int alarmId)
{
    alarms[alarmId] = 0;
}

void Alarms::clearAll(void)
{
    memset(alarms, 0, sizeof(alarms));
}
