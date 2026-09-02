
#ifndef SCHEDULLER_H
#define SCHEDULLER_H

#define SCHEDULLER_SIZE (32)

class Scheduller
{
public:
    class Task
    {
    public:
        virtual const char *getName(void) = 0;
        virtual void prepare(void) = 0;
        virtual int need(long int time) = 0;
        virtual void run(long int time) = 0;
        virtual void stop(void) = 0;

        void incrementExpendedTime(long int elapsed) { expendedTime += elapsed; }
        long int getExpendedTime(void) { return expendedTime; }

    protected:
        long int expendedTime;

    private:
    };

    void init(void);
    void addTask(Scheduller::Task *task, int executionOrder);
    void run(void);

protected:
private:
    Scheduller::Task *tasks[SCHEDULLER_SIZE];
    int period;
};

#endif
