
#ifndef LOGGER_ABSTRACT_H
#define LOGGER_ABSTRACT_H

#define LOGGER_LEVEL_VALUE_NO_LOG 6
#define LOGGER_LEVEL_VALUE_ERROR 5
#define LOGGER_LEVEL_VALUE_WARN 4
#define LOGGER_LEVEL_VALUE_INFO 3
#define LOGGER_LEVEL_VALUE_NOTICE 2
#define LOGGER_LEVEL_VALUE_DBG 1

class LoggerAbstract
{
public:
    enum Level
    {
        NO_LOG = LOGGER_LEVEL_VALUE_NO_LOG,
        ERROR = LOGGER_LEVEL_VALUE_ERROR,
        WARN = LOGGER_LEVEL_VALUE_WARN,
        INFO = LOGGER_LEVEL_VALUE_INFO,
        NOTICE = LOGGER_LEVEL_VALUE_NOTICE,
        DBG = LOGGER_LEVEL_VALUE_DBG
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
