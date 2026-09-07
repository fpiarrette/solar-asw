#include "TaskRest.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"

#define LOG_PREFIX "REST task "

http_context_t TaskRest::context;

TaskRest::TaskRest()
{
    /* default port value */
    port = 8080;
}

const char *TaskRest::getName(void)
{
    return "REST task";
}

void TaskRest::prepare(void)
{
    daemon = MHD_start_daemon(
        0,
        port,
        NULL,
        NULL,            /* accept policy call back */
        &requestHandler, /* request handlers */
        NULL,            /* call back argument*/
        MHD_OPTION_END);

    if (daemon == NULL)
    {
        L_ERROR("starting MHD daemon");

        return;
    }
    else
    {
        L_DEBUG("REST HTTP/JSON listening on %d", port);
    }

    L_NOTICE(LOG_PREFIX "prepared");
}

Scheduller::Task::Result TaskRest::run(long int time)
{
    context.worked = 0;

    MHD_run(daemon);

    if (context.worked)
        return Scheduller::Task::Result::WORKED;
    else
        return Scheduller::Task::Result::IDLE;
}

enum MHD_Result TaskRest::requestHandlerSingle(
    void *cls,
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    const char *uploadData,
    size_t *uploadDataSize,
    void **con_cls)
{
    L_DEBUG("Process %s method %s", method, url);

    const char *body = "{ \"id\": 123, \"message\": \"Hello World\" }";

    MHD_Result ret = reply(connection, MHD_HTTP_OK, body, strlen(body));

    context.worked = 1;

    return ret;
}

MHD_Result TaskRest::reply(struct MHD_Connection *connection, int code, const char *body, size_t size)
{
    MHD_Response *response = MHD_create_response_from_buffer(size, (void *)body, MHD_RESPMEM_PERSISTENT);

    MHD_Result ret = MHD_queue_response(connection, code, response);

    MHD_destroy_response(response);

    return ret;
}

enum MHD_Result TaskRest::requestHandlerParts(
    void *cls,
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    const char *uploadData,
    size_t *uploadDataSize,
    void **con_cls)
{
    MHD_Result ret = MHD_YES;

    if (con_cls == NULL)
    {
        *con_cls = &context;
    }

    if (*uploadDataSize > 0)
    {
        http_context_t *c = (http_context_t *)*con_cls;

        memcpy(&c->buffer[c->size], uploadData, *uploadDataSize);

        c->size += *uploadDataSize;

        *uploadDataSize = 0;
    }
    else
    {
        /* process POST method */
        L_DEBUG("Process %s method %s", method, url);

        const char *body = "{ \"result\": 0, \"message\": \"OK\" }";

        ret = reply(connection, MHD_HTTP_OK, body, strlen(body));
    }

    context.worked = 1;

    return ret;
}

void TaskRest::stop(void)
{
    if (daemon != NULL)
    {
        L_DEBUG("daemon is available");

        MHD_stop_daemon(daemon);

        daemon = NULL;
    }

    L_NOTICE(LOG_PREFIX "stopped");
}

enum MHD_Result TaskRest::requestHandler(
    void *cls,
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    const char *uploadData,
    size_t *uploadDataSize,
    void **con_cls)
{
    if (strcmp(MHD_HTTP_METHOD_GET, method) == 0)
    {
        return requestHandlerSingle(cls,
                                    connection,
                                    url,
                                    method,
                                    version,
                                    uploadData,
                                    uploadDataSize,
                                    con_cls);
    }
    else if (strcmp(MHD_HTTP_METHOD_POST, method) == 0)
    {
        return requestHandlerParts(cls,
                                   connection,
                                   url,
                                   method,
                                   version,
                                   uploadData,
                                   uploadDataSize,
                                   con_cls);
    }
    else if (strcmp(MHD_HTTP_METHOD_PUT, method) == 0)
    {
        return requestHandlerParts(cls,
                                   connection,
                                   url,
                                   method,
                                   version,
                                   uploadData,
                                   uploadDataSize,
                                   con_cls);
    }
    else if (strcmp(MHD_HTTP_METHOD_PATCH, method) == 0)
    {
        return requestHandlerParts(cls,
                                   connection,
                                   url,
                                   method,
                                   version,
                                   uploadData,
                                   uploadDataSize,
                                   con_cls);
    }
    else if (strcmp(MHD_HTTP_METHOD_DELETE, method) == 0)
    {
        return requestHandlerSingle(cls,
                                    connection,
                                    url,
                                    method,
                                    version,
                                    uploadData,
                                    uploadDataSize,
                                    con_cls);
    }

    return MHD_YES;
}