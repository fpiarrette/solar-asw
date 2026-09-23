
#ifndef ALARMS_H
#define ALARMS_H

#define ALARMS_SIZE (32)
/* each alarm count with a coockie space of 8 integers */
#define ALARMS_COCKIE_SIZE (8)

class Alarms
{
public:
    static Alarms *getInstance(void);

    int get(int alarmId);
    void set(int alarmId);
    void clear(int alarmId);
    void clearAll(void);

    class Cookie
    {
    public:
    protected:
    private:
        int space[ALARMS_COCKIE_SIZE];
    };

    void *getCookie(int alarmId);
    void setCookie(int alarmId, void *c);

protected:
private:
    static Alarms instance;
    int alarms[ALARMS_SIZE];
    Cookie cookies[ALARMS_SIZE];
};

#endif
