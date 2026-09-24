#include "RestHandlerStatistics.h"

#include "Alarms.h"
#include "Logger.h"
#include "setup.h"

#include <jansson.h>
#include <stdio.h>

#define LOG_PREFIX "REST handler statistics "

enum MHD_Result RestHandlerStatistics::handle(
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    char *requestBody,
    int size)
{
    json_t *root = json_object();

    json_object_set_new(root, "uplink", json_integer(0));
    json_object_set_new(root, "downllink", json_integer(0));

    char *json = json_dumps(root, JSON_INDENT(2));

    /* send response */
    MHD_Result result = reply(connection, MHD_HTTP_OK, json, strlen(json));

    free(json);
    json_decref(root);

    return result;
}

