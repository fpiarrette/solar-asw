
#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_E_OK (0)
#define CONFIG_E_INVALID (-1)

class Config
{
public:
    enum Error {
        E_OK = 0,
        E_TRY = -1,
        E_ARG = -2,
        E_STA = -3,
        E_INT = 4
    };

    Config::Error init(int argc, char *argv[]);
    static Config *getInstance(void);
    int isUseStdout(void);
    int isUseSyslog(void);
    int isShowHelp(void);
    void help(int argc, char *argv[]);
    int getTimeDeliveryLimit(void);
    int getBufferSizeLimit(void);
    int isFromModem(void);
    int isToModem(void);
    int getLogLevel();

protected:
private:
    static Config instance;
    int logLevel;
    int useSyslog;
    int useStdout;
    int showHelp;
    int timeDeliveryLimit;
    int bufferSizeLimit;
    int toModem;
    int fromModem;
};

#endif
