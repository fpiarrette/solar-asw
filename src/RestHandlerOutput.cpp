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

    /* publish Alarm to notify that configured channer shall be used */
    int buffer[5];

    if (sscanf(ipString, "%d.%d.%d.%d", &buffer[0], &buffer[1], &buffer[2], &buffer[3]) != 4)
    {
        L_ERROR("Error parsing JSON: IP string value is wrong");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    buffer[4] = (int)portInteger;

    Alarms::getInstance()->set(SETUP_ALARM_NEW_OUTPUT);
    Alarms::getInstance()->setCookie(SETUP_ALARM_NEW_OUTPUT, buffer);

    L_DEBUG("using %d.%d.%d.%d:%d", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

    json_decref(rootNode);

    /* send response */
    MHD_Result result = replyEmpty(connection, MHD_HTTP_NO_CONTENT);

    return result;
}
