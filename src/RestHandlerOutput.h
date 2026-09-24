
#ifndef REST_HANDLER_OUTPUT_H
#define REST_HANDLER_OUTPUT_H

#include "RestHandler.h"

#include "ChannelSocketClient.h"

class RestHandlerOutput : public RestHandler
{
public:
    enum MHD_Result handle(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

    void setOutput(ChannelSocketClient *outputChannel);

protected:
    int reconfigureOutput(const char *ipString, int port);
private:
    ChannelSocketClient *outputChannel;
};

#endif
