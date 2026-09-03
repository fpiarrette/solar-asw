#include "Config.h"
#include "Logger.h"

#include "ChannelNull.h"
#include "ChannelSocketClient.h"
#include "ChannelSocketServer.h"
#include "ChannelSpi.h"

#include "Gpio.h"

#include "Scheduller.h"
#include "TaskFromModem.h"
#include "TaskHumanInterface.h"
#include "TaskIdle.h"
#include "TaskRest.h"
#include "TaskToModem.h"

#include <stdlib.h>

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

        if (Config::getInstance()->isShowHelp())
        {
            Config::getInstance()->help(argc, argv);
        }
        else
        {

#ifdef FORCE_TEST_CONTEXT
            /* in host it's not assumed /dev/gpiochip* and gpio module/driver */
            Gpio::configure(Gpio::Type::MOCK);
#else
            /* in Linux ARM it's assumed /dev/gpiochip* and gpio module/driver */
            Gpio::configure(Gpio::Type::MODULE);
#endif
            /* Line 0 as input is just an example */
            Gpio::getInstance()->configure(0, GpioAbstract::Type::IN);

            Scheduller scheduller;

            /* tasks */
            TaskFromModem taskFromModem;
            TaskToModem taskToModem;
            TaskHumanInterface taskHumanInterface;
            TaskIdle taskIdle;
            TaskRest taskRest;

            /* channels */
            ChannelSocketClient channelSocketClient;
            ChannelSocketServer channelSocketServer;
            ChannelSpi channelSpi;
            ChannelNull channelNull;

            /* all channels are configured independently of the mode, because HOST mode could use a convination of them */
            /* specific configuration for socket client */
            channelSocketClient.setIpAddress(Config::getInstance()->getDestinationIpAddress());
            channelSocketClient.setPort(Config::getInstance()->getDestinationPort());
            /* specific configuration for socket server */
            channelSocketServer.setPort(Config::getInstance()->getListeningPort());
            /* specific configuration for SPI */
            /* TBC */

            if (Config::getInstance()->isFromModem())
            {
                /* specific task configuration */
                taskFromModem.setTimeDeliveryLimit(Config::getInstance()->getTimeDeliveryLimit());
                taskFromModem.setSizeLimit(Config::getInstance()->getBufferSizeLimit());

                /* wiring */
                taskFromModem.setSource(&channelSpi);
                taskFromModem.setSink(&channelSocketClient);
                scheduller.addTask(&taskFromModem, 2);
            }
            else
            {
                /* specific task configuration */

                /* wiring */
                taskToModem.setSource(&channelSocketServer);
                taskToModem.setSink(&channelSpi);
                scheduller.addTask(&taskToModem, 2);
            }

            /* manage REST interface */
            scheduller.addTask(&taskRest, 16);

            /* manage human/GPIO interface */
            scheduller.addTask(&taskHumanInterface, 20);

            scheduller.addTask(&taskIdle, 31);
            taskIdle.setScheduller(&scheduller);

#ifdef FORCE_TEST_CONTEXT
            /* This compile time option allows to overwrite proper context and configure the process with a test context just for host platform and debug purpose */
            if (Config::getInstance()->isFromModem())
            {
                /* specific task configuration */
                taskFromModem.setSource(&channelSocketServer);
            }
            else
            {
                /* specific task configuration */
                taskToModem.setSink(&channelSocketClient);
            }

#endif

            /* execute all schedulled tasks */
            scheduller.run();
        }

        L_INFO("Finishing...");
        Logger::getInstance()->stop();
    }
    else
    {
        Config::getInstance()->help(argc, argv);
    }

    return EXIT_SUCCESS;
}
