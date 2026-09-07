
#ifndef SCHEDULLER_H
#define SCHEDULLER_H

#define SCHEDULLER_SIZE (32)

class Scheduller
{
public:
    class Task
    {
    public:
        enum Result
        {
            WORKED,
            IDLE
        };
        Task()
        {
            expendedTime = 0;
        }
        virtual const char *getName(void) = 0;
        virtual void prepare(void) = 0;
        virtual Scheduller::Task::Result run(long int time) = 0;
        virtual void stop(void) = 0;

        void incrementExpendedTime(long int elapsed) { expendedTime += elapsed; }
        long int getExpendedTime(void) { return expendedTime; }

    protected:
        long int expendedTime;

    private:
    };

    Scheduller();
    void addTask(Scheduller::Task *task, int executionOrder);
    void run(void);

    int hasMoreTasks(void);
    Scheduller::Task *getNextTask(void);
    void pause(void) { paused = 1; }
    void resume(void) { paused = 0; }
    void kill(void) { terminated = 1; }

protected:
    void publishTimeAlarms(long int time);

private:
    Scheduller::Task *tasks[SCHEDULLER_SIZE];
    int period, nextTask;
    long int globalStartTime;
    long int previousTenthSecondCounter;
    long int previousSecondCounter;
    long int previousHundredMiliSeconds;
    int terminated, paused;
};

#endif
