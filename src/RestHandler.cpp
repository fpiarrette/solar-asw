#include "RestHandler.h"

#include "Logger.h"
#include <stdio.h>

#define LOG_PREFIX "REST handler "

MHD_Result RestHandler::replyEmpty(struct MHD_Connection *connection, int code)
{
    return reply(connection, code, 0x0, 0);
}

MHD_Result RestHandler::reply(struct MHD_Connection *connection, int code, const char *body, size_t size)
{
    MHD_Response *response;
    response = MHD_create_response_from_buffer(size, (void *)body, MHD_RESPMEM_MUST_COPY);
    MHD_add_response_header(response, "Content-Type", "application/json");
    MHD_Result ret = MHD_queue_response(connection, code, response);
    MHD_destroy_response(response);

    return ret;
}
