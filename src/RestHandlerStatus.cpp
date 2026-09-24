#include "RestHandlerStatus.h"

#include "Alarms.h"
#include "Logger.h"
#include "setup.h"

#include <jansson.h>
#include <stdio.h>

#define LOG_PREFIX "REST handler status "

enum MHD_Result RestHandlerStatus::handle(
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    char *requestBody,
    int size)
{

    json_t *root = json_object();

    json_t *alarms = json_array();

    for (int n = 0; n < ALARMS_SIZE; n++)
    {
        json_array_append_new(alarms, json_integer(Alarms::getInstance()->get(n)));
    }

    json_object_set_new(root, "alarms", alarms);

    char *json = json_dumps(root, JSON_INDENT(2));

    /* send response */
    MHD_Result result = reply(connection, MHD_HTTP_OK, json, strlen(json));

    json_decref(root);

    return result;
}
