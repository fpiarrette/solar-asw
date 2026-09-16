#include "RestReplier.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"

#include <stdio.h>

#define LOG_PREFIX "REST replier "

MHD_Result RestReplier::reply(struct MHD_Connection *connection, int code, const char *body, size_t size)
{
    MHD_Response *response = MHD_create_response_from_buffer(size, (void *)body, MHD_RESPMEM_PERSISTENT);

    MHD_Result ret = MHD_queue_response(connection, code, response);

    MHD_destroy_response(response);

    return ret;
}

enum MHD_Result RestReplier::process(
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version)
{
    L_DEBUG("%s '%s'", method, url);

    const char *statusTemplate = "{ \"alarms\": [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d] }";
    char statusBuffer[256];

    sprintf(statusBuffer, statusTemplate,
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

    return reply(connection, MHD_HTTP_OK, statusBuffer, strlen(statusBuffer));
}
