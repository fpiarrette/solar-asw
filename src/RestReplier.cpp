#include "RestReplier.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"

#include <jansson.h>
#include <stdio.h>

#define LOG_PREFIX "REST replier "

MHD_Result RestReplier::reply(struct MHD_Connection *connection, int code, const char *body, size_t size)
{
    MHD_Response *response = MHD_create_response_from_buffer(size, (void *)body, MHD_RESPMEM_PERSISTENT);
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
        return processNotFound(connection, url, method, version, requestBody, size);
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

    const char *t = "{ \"alarms\": [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d] }";
    char b[256];

    /* get status */
    /* build response */
    sprintf(b, t,
            Alarms::getInstance()->get(0),
            Alarms::getInstance()->get(1),
            Alarms::getInstance()->get(2),
            Alarms::getInstance()->get(3),
            Alarms::getInstance()->get(4),
            Alarms::getInstance()->get(5),
            Alarms::getInstance()->get(6),
            Alarms::getInstance()->get(7),
            Alarms::getInstance()->get(8),
            Alarms::getInstance()->get(9),
            Alarms::getInstance()->get(10),
            Alarms::getInstance()->get(11),
            Alarms::getInstance()->get(12),
            Alarms::getInstance()->get(13),
            Alarms::getInstance()->get(14),
            Alarms::getInstance()->get(15),
            Alarms::getInstance()->get(16),
            Alarms::getInstance()->get(17),
            Alarms::getInstance()->get(18),
            Alarms::getInstance()->get(19),
            Alarms::getInstance()->get(20),
            Alarms::getInstance()->get(21),
            Alarms::getInstance()->get(22),
            Alarms::getInstance()->get(23),
            Alarms::getInstance()->get(24),
            Alarms::getInstance()->get(25),
            Alarms::getInstance()->get(26),
            Alarms::getInstance()->get(27),
            Alarms::getInstance()->get(28),
            Alarms::getInstance()->get(29),
            Alarms::getInstance()->get(30),
            Alarms::getInstance()->get(31));

    /* send response */
    return reply(connection, MHD_HTTP_OK, b, strlen(b));
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
    const char *t = "{ \"result\": %d }";
    char b[256];

    /* parse request body */
    /* apply configuration */
    /* build response */

    L_DEBUG("body '%s'", requestBody);
    L_DEBUG("size '%d'", size);

    sprintf(b, t, 0);

    /* send response */
    return reply(connection, MHD_HTTP_OK, b, strlen(b));
}

enum MHD_Result RestReplier::processNotFound(
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    char *requestBody,
    int size)
{

    const char *t = "{ \"error\": %d }";
    char b[256];

    sprintf(b, t, 404);

    return reply(connection, MHD_HTTP_NOT_FOUND, b, strlen(b));
}
