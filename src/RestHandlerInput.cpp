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

    /* publish Alarm to notify that configured channer shall be used */
    if (v == 0)
    {
        Alarms::getInstance()->set(SETUP_ALARM_INPUT_CHANNEL_0);
    }
    else
    {
        Alarms::getInstance()->set(SETUP_ALARM_INPUT_CHANNEL_1);
    }

    L_DEBUG("using channel=%lld\n", v);

    json_decref(root);

    /* send response */
    MHD_Result result = replyEmpty(connection, MHD_HTTP_NO_CONTENT);

    return result;
}

