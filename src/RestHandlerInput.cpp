#include "RestHandlerInput.h"

#include "Alarms.h"
#include "Logger.h"
#include "setup.h"

#include <jansson.h>
#include <stdio.h>

#define LOG_PREFIX "REST handler input "

enum MHD_Result RestHandlerInput::handle(
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    char *requestBody,
    int size)
{

    json_error_t error;
    json_t *root = json_loads(requestBody, 0, &error);
    if (!root)
    {
        L_ERROR("Error parsing JSON: %s\n", error.text);
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    json_t *channel = json_object_get(root, "channel");
    if (!channel)
    {
        L_ERROR("Error parsing JSON: channel node is not present");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    if (!json_is_integer(channel))
    {
        L_ERROR("Error parsing JSON: channel node is not integer");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    json_int_t v = json_integer_value(channel);

    int reconf = reconfigureInput((int)v);

    json_decref(root);

    /* send response */
    MHD_Result result = replyEmpty(connection, reconf == 0 ? MHD_HTTP_NO_CONTENT : MHD_HTTP_INTERNAL_SERVER_ERROR);

    return result;
}

int RestHandlerInput::reconfigureInput(int channel)
{
    Channel::Error r;

    L_DEBUG("using channel %d", channel);

    r = inputChannel->stop();

    L_DEBUG("stopping: %d", r);

    if ((r != Channel::Error::E_OK) && (r != Channel::Error::E_STA))
    {
        return -1;
    }

    r = inputChannel->setPort(channel);

    L_DEBUG("setting port: %d", r);

    if (r != Channel::Error::E_OK)
    {
        return -1;
    }

    r = inputChannel->start();

    L_DEBUG("starting: %d", r);

    if (r != Channel::Error::E_OK)
    {
        return -1;
    }

    return 0;
}

void RestHandlerInput::setInput(ChannelSocketServer *i)
{
    inputChannel = i;
}
