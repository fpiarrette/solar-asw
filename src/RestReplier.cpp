#include "RestReplier.h"

#include "Alarms.h"
#include "Logger.h"
#include "setup.h"

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
    else if (strcmp("/api/input", url) == 0)
    {
        return processInput(connection, url, method, version, requestBody, size);
    }
    else if (strcmp("/api/output", url) == 0)
    {
        return processOutput(connection, url, method, version, requestBody, size);
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

enum MHD_Result RestReplier::processInput(
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

enum MHD_Result RestReplier::processOutput(
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

    json_t *ip = json_object_get(root, "ip");
    if (!ip)
    {
        L_ERROR("Error parsing JSON: ip node is not present");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    const char *i = json_string_value(ip);
    if (!i)
    {
        L_ERROR("Error parsing JSON: ip node is not a string");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    json_t *port = json_object_get(root, "port");
    if (!port)
    {
        L_ERROR("Error parsing JSON: port node is not present");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    if (!json_is_integer(port))
    {
        L_ERROR("Error parsing JSON: port node is not integer");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    json_int_t p = json_integer_value(port);

    /* publish Alarm to notify that configured channer shall be used */
    Alarms::getInstance()->set(SETUP_ALARM_NEW_OUTPUT);

    L_DEBUG("using %s:%lld", i, p);

    json_decref(root);

    /* send response */
    MHD_Result result = replyEmpty(connection, MHD_HTTP_NO_CONTENT);

    return result;
}