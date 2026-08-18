
#ifndef LOGGER_ABSTRACT_H
#define LOGGER_ABSTRACT_H

class LoggerAbstract
{
public:
    virtual void init(void) = 0;
    virtual void start(const char *name) = 0;
    virtual void stop(void) = 0;

    virtual void error(const char *format, ...) = 0;
    virtual void warning(const char *format, ...) = 0;
    virtual void info(const char *format, ...) = 0;
    virtual void notice(const char *format, ...) = 0;
    virtual void debug(const char *format, ...) = 0;
};

#endif
