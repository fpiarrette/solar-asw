#include "RestReplier.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"

#include <jansson.h>
#include <stdio.h>

#define LOG_PREFIX "REST replier "

MHD_Result RestReplier::replyEmpty(struct MHD_Connection *connection, int code)
{
    return reply(connection, code, 0x0, 0);
}

MHD_Result RestReplier::reply(struct MHD_Connection *connection, int code, const char *body, size_t size)
{
    MHD_Response *response;
    response = MHD_create_response_from_buffer(size, (void *)body, MHD_RESPMEM_MUST_COPY);
    MHD_add_response_header(response, "Content-Type", "application/json");
    MHD_Result ret = MHD_queue_response(connection, code, response);
    MHD_destroy_response(response);

    return ret;
}

enum MHD_Result RestReplier::process(
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    char *requestBody,
    int size)
{
    L_DEBUG("%s '%s'", method, url);

    if (strcmp("/api/status", url) == 0)
    {
        return processStatus(connection, url, method, version, requestBody, size);
    }
    else if (strcmp("/api/statistics", url) == 0)
    {
        return processStatistics(connection, url, method, version, requestBody, size);
    }
    else if (strcmp("/api/config", url) == 0)
    {
        return processConfig(connection, url, method, version, requestBody, size);
    }
    else
    {
        return replyEmpty(connection, MHD_HTTP_NOT_FOUND);
    }
}

enum MHD_Result RestReplier::processStatus(
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

enum MHD_Result RestReplier::processStatistics(
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

enum MHD_Result RestReplier::processConfig(
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

    json_t *mode = json_object_get(root, "mode");
    json_t *speed = json_object_get(root, "speed");

    (void)mode;

    if (json_is_integer(speed))
    {
        L_DEBUG("speed=%lld\n", (long long)json_integer_value(speed));
    }

    json_decref(root);

    /* send response */
    MHD_Result result = replyEmpty(connection, MHD_HTTP_NO_CONTENT);

    return result;
}