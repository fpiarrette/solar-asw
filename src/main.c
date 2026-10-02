#include "Config.h"
#include "Logger.h"

#include "ChannelMeter.h"
#include "ChannelNull.h"
#include "ChannelSocketClient.h"
#include "ChannelSocketServer.h"
#include "ChannelSpiMaster.h"
#include "ChannelSpiSlave.h"

#include "Gpio.h"

#include "Platform.h"

#include "Scheduller.h"
#include "TaskFromModem.h"
#include "TaskHumanInterface.h"
#include "TaskIdle.h"
#include "TaskKiller.h"
#include "TaskRest.h"
#include "TaskToModem.h"

#include "RestHandlerInput.h"
#include "RestHandlerMux.h"
#include "RestHandlerOutput.h"
#include "RestHandlerStatistics.h"
#include "RestHandlerStatus.h"

#include <stdlib.h>

static void configure_and_run(void);

int main(int argc, char *argv[])
{
    /* parse arguments */
    if (Config::getInstance()->init(argc, argv) == Config::Error::E_OK)
    {

        /* initialization */
        if (Config::getInstance()->isUseStdout())
            Logger::config(Logger::Type::STDOUT);
        else
            Logger::config(Logger::Type::SYSLOG);

        Logger::getInstance()->setLevel(Config::getInstance()->getLogLevel());
        Logger::getInstance()->start("Modem TCP converter");

        L_INFO("Starting...");

        L_NOTICE(Platform::getInstance()->getName());

        if (Config::getInstance()->isShowHelp())
        {
            Config::getInstance()->help(argc, argv);
        }
        else
        {
            /* perform all object required wiring and run the process */
            configure_and_run();
        }

        /* free platform openned resources */
        Platform::getInstance()->shutdown();

        L_INFO("Finishing...");
        Logger::getInstance()->stop();
    }
    else
    {
        Config::getInstance()->help(argc, argv);
    }

    return EXIT_SUCCESS;
}

static void configure_and_run(void)
{
    /* Platform implementation fixed at compilation time */
    Platform::getInstance()->init();

    /* channels */
    ChannelSocketClient channelSocketClient;
    ChannelMeter channelSocketClientMeter(channelSocketClient);
    ChannelSocketServer channelSocketServer;
    ChannelMeter channelSocketServerMeter(channelSocketServer);
    ChannelSocketServer channelSocketKillStop;
    ChannelSpiMaster channelSpiMaster;
    ChannelSpiSlave channelSpiSlave;
    ChannelNull channelNull;

    Scheduller scheduller;

    /* tasks */
#if PLATFORM_ID == PLATFORM_HOST
    L_WARNING("In host platform SPI channel is replaced by socket client and server channels");
    TaskFromModem taskFromModem(channelSocketServerMeter, channelSocketClientMeter);
    TaskToModem taskToModem(channelSocketServerMeter, channelSocketClientMeter);
#else
    TaskFromModem taskFromModem(channelSpiSlave, channelSocketClientMeter);
    TaskToModem taskToModem(channelSocketServerMeter, channelSpiMaster);
#endif

    TaskHumanInterface taskHumanInterface;
    TaskIdle taskIdle;
    TaskKiller taskKiller;
    TaskRest taskRest;
    RestHandlerInput restHandlerInput;
    RestHandlerMux restHandlerMux;
    RestHandlerOutput restHandlerOutput;
    RestHandlerStatistics restHandlerStatistics;
    RestHandlerStatus restHandlerStatus;
    taskRest.addHandler("/api/input", &restHandlerInput);
    taskRest.addHandler("/api/mux", &restHandlerMux);
    taskRest.addHandler("/api/output", &restHandlerOutput);
    taskRest.addHandler("/api/status", &restHandlerStatus);
    taskRest.addHandler("/api/statistics", &restHandlerStatistics);

    restHandlerInput.setInput(&channelSocketServer);
    restHandlerOutput.setOutput(&channelSocketClient);

    /* all channels are configured independently of the mode, because HOST mode could use a convination of them */
    /* specific configuration for socket client */
    channelSocketClient.setIpAddress(Config::getInstance()->getDestinationIpAddress());
    channelSocketClient.setPort(Config::getInstance()->getDestinationPort());
    /* specific configuration for socket server */
    channelSocketServer.setPort(Config::getInstance()->getListeningPort());
    /* specific configuration for SPI */
    channelSpiMaster.setDeviceName(Config::getInstance()->getSpiMasterName());
    channelSpiMaster.setSpeed(Config::getInstance()->getSpiMasterSpeed());
    channelSpiMaster.setClockPolarity(Config::getInstance()->getSpiMasterClockPolarity());
    channelSpiMaster.setClockPhase(Config::getInstance()->getSpiMasterClockPhase());
    channelSpiMaster.setBits(Config::getInstance()->getSpiMasterBits());

    /* specific task configuration */
    taskFromModem.setTimeDeliveryLimit(Config::getInstance()->getTimeDeliveryLimit());
    taskFromModem.setSizeLimit(Config::getInstance()->getBufferSizeLimit());

    if (Config::getInstance()->isFromModem())
    {
        scheduller.addTask(&taskFromModem, 2);
    }
    else
    {
        scheduller.addTask(&taskToModem, 2);
    }

    /* set task killer a reception channel */
    channelSocketKillStop.setPort(9090);
    taskKiller.setSource(&channelSocketKillStop);
    taskKiller.setScheduller(&scheduller);

    /* manage REST interface */
    scheduller.addTask(&taskRest, 16);

    /* manage human/GPIO interface */
    scheduller.addTask(&taskHumanInterface, 20);

    /* manage graceful kill stop flags */
    scheduller.addTask(&taskKiller, 26);

    scheduller.addTask(&taskIdle, 31);
    taskIdle.setScheduller(&scheduller);

    /* execute all schedulled tasks */
    scheduller.run();
}
