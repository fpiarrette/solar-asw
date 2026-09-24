
#ifndef REST_HANDLER_INPUT_H
#define REST_HANDLER_INPUT_H

#include "RestHandler.h"

#include "ChannelSocketServer.h"

class RestHandlerInput : public RestHandler
{
public:
    enum MHD_Result handle(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

    void setInput(ChannelSocketServer *inputChannel);

protected:
    int reconfigureInput(int channel);
private:
    ChannelSocketServer *inputChannel;
};

#endif
