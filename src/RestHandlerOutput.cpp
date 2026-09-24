#include "RestHandlerOutput.h"

#include "Alarms.h"
#include "Logger.h"
#include "setup.h"

#include <jansson.h>
#include <stdio.h>

#define LOG_PREFIX "REST handler output "

enum MHD_Result RestHandlerOutput::handle(
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    char *requestBody,
    int size)
{

    json_error_t error;
    json_t *rootNode = json_loads(requestBody, 0, &error);
    if (!rootNode)
    {
        L_ERROR("Error parsing JSON: %s\n", error.text);
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    json_t *ipNode = json_object_get(rootNode, "ip");
    if (!ipNode)
    {
        L_ERROR("Error parsing JSON: ip node is not present");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    const char *ipString = json_string_value(ipNode);
    if (!ipString)
    {
        L_ERROR("Error parsing JSON: ip node is not a string");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    json_t *portNode = json_object_get(rootNode, "port");
    if (!portNode)
    {
        L_ERROR("Error parsing JSON: port node is not present");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    if (!json_is_integer(portNode))
    {
        L_ERROR("Error parsing JSON: port node is not integer");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    json_int_t portInteger = json_integer_value(portNode);

    /* configure channel socket client */

    int reconf = reconfigureOutput(ipString, (int)portInteger);

    json_decref(rootNode);

    /* send response */
    MHD_Result result = replyEmpty(connection, reconf == 0 ? MHD_HTTP_NO_CONTENT : MHD_HTTP_INTERNAL_SERVER_ERROR);

    return result;
}

int RestHandlerOutput::reconfigureOutput(const char *ipString, int port)
{
    Channel::Error r;

    L_DEBUG("using %s:%d", ipString, port);

    r = outputChannel->stop();

    L_DEBUG("stopping: %d", r);

    if ((r != Channel::Error::E_OK) && (r != Channel::Error::E_STA))
    {
        return -1;
    }

    r = outputChannel->setIpAddress(ipString);

    L_DEBUG("setting ip: %d", r);

    if (r != Channel::Error::E_OK)
    {
        return -1;
    }

    r = outputChannel->setPort(port);

    L_DEBUG("setting port: %d", r);

    if (r != Channel::Error::E_OK)
    {
        return -1;
    }

    r = outputChannel->start();

    L_DEBUG("starting: %d", r);

    if (r != Channel::Error::E_OK)
    {
        return -1;
    }

    return 0;
}

void RestHandlerOutput::setOutput(ChannelSocketClient *o)
{
    outputChannel = o;
}