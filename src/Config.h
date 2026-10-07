
#ifndef CONFIG_H
#define CONFIG_H

#include <jansson.h>

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
    const char * getDestinationIpAddress(void);
    int getDestinationPort(void);
    int getListeningPort(void);
    const char *getSpiMasterName(void);
    unsigned int getSpiMasterSpeed(void);
    unsigned char getSpiMasterClockPolarity(void);
    unsigned char getSpiMasterClockPhase(void);
    unsigned char getSpiMasterBits(void);

protected:
    void setDefaultValues(void);
    Config::Error setCustomValues(void);
    Config::Error getIntValue(json_t *parent, const char *nodeName, int *variable);
    Config::Error getUnsignedIntValue(json_t *parent, const char *nodeName, unsigned int *variable);
    Config::Error getCharValue(json_t *parent, const char *nodeName, char *variable);
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
    /* 4 3 digit numbers + 3 dots + null termination */
    char destinationIpAddress[4 * 3 + 3 * 1 + 1];
    int destinationPort;
    int listeningPort;
    char spiMasterDeviceName[128];
    unsigned int spiMasterSpeed;
    unsigned int spiMasterClockPolarity;
    unsigned int spiMasterClockPhase;
    unsigned int spiMasterBits;
    char configurationFile[128];
};

#endif
