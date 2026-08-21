
#ifndef LOGGER_ABSTRACT_H
#define LOGGER_ABSTRACT_H

class LoggerAbstract
{
public:
    enum Level
    {
        NO_LOG = 6,
        ERROR = 5,
        WARN = 4,
        INFO = 3,
        NOTICE = 2,
        DBG = 1
    };

    virtual void init(void) = 0;
    virtual void start(const char *name) = 0;
    virtual void stop(void) = 0;

    void error(const char *format, ...);
    void warning(const char *format, ...);
    void info(const char *format, ...);
    void notice(const char *format, ...);
    void debug(const char *format, ...);

    void setLevel(int l);
    int isAllowed(Level l);

protected:
    virtual void logError(const char *format, ...) = 0;
    virtual void logWarning(const char *format, ...) = 0;
    virtual void logInfo(const char *format, ...) = 0;
    virtual void logNotice(const char *format, ...) = 0;
    virtual void logDebug(const char *format, ...) = 0;
    int level;

private:
};

#endif
