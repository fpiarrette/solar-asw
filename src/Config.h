
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
private:
    static Config instance;
    int logLevel;
    int useSyslog;
    int useStdout;
    int showHelp;
};

#endif
