
#ifndef ALARMS_H
#define ALARMS_H

#define ALARMS_SIZE (32)

class Alarms
{

    static Alarms *getInstance(void);

    int get(int alarmId);
    void set(int alarmId);
    void clear(int alarmId);
    void clearAll(void);

protected:
private:
    static Alarms instance;
    int alarms[ALARMS_SIZE];
};

#endif
