#include "RestHandlerStatisticsToModem.h"

#include "Alarms.h"
#include "Logger.h"
#include "setup.h"

#include <jansson.h>
#include <stdio.h>

#define LOG_PREFIX "REST handler statistics to MODEM"

enum MHD_Result RestHandlerStatisticsToModem::handle(
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    char *requestBody,
    int size)
{
    json_t *root = json_object();

    if (Alarms::getInstance()->get(SETUP_ALARM_TO_MODEM_METER_ACCUMULATED))
    {
        size_t *a = (size_t *)Alarms::getInstance()->getCookie(SETUP_ALARM_TO_MODEM_METER_ACCUMULATED);
        Alarms::getInstance()->clear(SETUP_ALARM_TO_MODEM_METER_ACCUMULATED);
        json_object_set_new(root, "accumulated", json_integer(*a));
    }
    else
    {
        json_object_set_new(root, "accumulated", json_integer(0));
    }

    char *json = json_dumps(root, JSON_INDENT(2));

    /* send response */
    MHD_Result result = reply(connection, MHD_HTTP_OK, json, strlen(json));

    free(json);
    json_decref(root);

    return result;
}
