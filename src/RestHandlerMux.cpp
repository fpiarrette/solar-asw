#include "RestHandlerMux.h"

#include "Logger.h"
#include "Platform.h"
#include "setup.h"

#include <jansson.h>
#include <stdio.h>

#define LOG_PREFIX "REST handler MUX "

enum MHD_Result RestHandlerMux::handle(
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

    json_t *muxInputNode = json_object_get(rootNode, "mux_input");
    if (!muxInputNode)
    {
        L_ERROR("Error parsing JSON: channel node is not present");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    if (!json_is_integer(muxInputNode))
    {
        L_ERROR("Error parsing JSON: channel node is not integer");
        return replyEmpty(connection, MHD_HTTP_BAD_REQUEST);
    }

    json_int_t v = json_integer_value(muxInputNode);

    Platform::getInstance()->getGpio()->set(SETUP_GPIO_MUX_PORT, SETUP_GPIO_MUX_LINE, ((int)v) != 0);

    json_decref(rootNode);

    /* send response */
    MHD_Result result = replyEmpty(connection, MHD_HTTP_NO_CONTENT);

    return result;
}
