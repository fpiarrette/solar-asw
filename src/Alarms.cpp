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

void Alarms::set(int alarmId, void *cookie, size_t size)
{
    alarms[alarmId] = 1;

    if (cookie != NULL && size > 0)
    {
        size_t s;
        s = size < sizeof(Cookie)? size : sizeof(Cookie);
        /* maximum copied is Cookie size */
        memcpy(&cookies[alarmId], cookie, s);
    }
}

void Alarms::clear(int alarmId)
{
    alarms[alarmId] = 0;
}

void Alarms::clearAll(void)
{
    memset(alarms, 0, sizeof(alarms));
}

void *Alarms::getCookie(int alarmId)
{
    return &cookies[alarmId];
}
