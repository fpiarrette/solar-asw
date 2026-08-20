
#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_E_OK (0)
#define CONFIG_E_INVALID (-1)

class Config
{
public:
    int init(int argc, char *argv[]);
    static Config *getInstance(void);
    int isUseStdout(void);
    int isUseSyslog(void);
    int isShowHelp(void);
    void help(int argc, char *argv[]);
    int getTimeDeliveryLimit(void);
    int getBufferSizeLimit(void);

protected:
private:
    static Config instance;
    int logLevel;
    int useSyslog;
    int useStdout;
    int showHelp;
    int timeDeliveryLimit;
    int bufferSizeLimit;
};

#endif
