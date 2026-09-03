
#ifndef ALARMS_H
#define ALARMS_H

#define ALARMS_SIZE (32)

#define ALARM_DEF_00 (0)
#define ALARM_DEF_01 (1)
#define ALARM_DEF_02 (2)
#define ALARM_DEF_03 (3)
#define ALARM_DEF_04 (4)
#define ALARM_DEF_05 (5)
#define ALARM_DEF_06 (6)
#define ALARM_DEF_07 (7)
#define ALARM_DEF_08 (8)
#define ALARM_DEF_09 (9)

#define ALARM_DEF_10 (10)
#define ALARM_DEF_11 (11)
#define ALARM_DEF_12 (12)
#define ALARM_DEF_13 (13)
#define ALARM_DEF_14 (14)
#define ALARM_DEF_15 (15)
#define ALARM_DEF_16 (16)
#define ALARM_DEF_17 (17)
#define ALARM_DEF_18 (18)
#define ALARM_DEF_19 (19)

#define ALARM_DEF_20 (20)
#define ALARM_DEF_21 (21)
#define ALARM_DEF_22 (22)
#define ALARM_DEF_23 (23)
#define ALARM_DEF_24 (24)
#define ALARM_DEF_25 (25)
#define ALARM_DEF_26 (26)
#define ALARM_DEF_27 (27)
#define ALARM_DEF_28 (28)
#define ALARM_DEF_29 (29)

#define ALARM_DEF_30 (30)
#define ALARM_DEF_31 (31)

class Alarms
{
public:
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
