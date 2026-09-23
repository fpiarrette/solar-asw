#include "TaskRest.h"

#include "Alarms.h"
#include "Logger.h"

#define LOG_PREFIX "REST task "

http_context_t TaskRest::context;

RestReplier *TaskRest::replier;

TaskRest::TaskRest()
{
    /* default port value */
    port = 8888;
}

void TaskRest::setReplier(RestReplier *r)
{
    replier = r;
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

    MHD_Result ret = replier->process(connection, url, method, version, 0, 0);

    context.worked = 1;

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
    if (*con_cls == NULL)
    {
        memset(&context, 0, sizeof(context));
        *con_cls = &context;
        L_DEBUG("Context initialized->first call");
        context.worked = 1;
        return MHD_YES;
    }
    else
    {
        if (*uploadDataSize > 0)
        {
            L_DEBUG("upload data %d", *uploadDataSize);
            http_context_t *c = (http_context_t *)*con_cls;
            memcpy(&c->buffer[c->size], uploadData, *uploadDataSize);
            c->size += *uploadDataSize;
            *uploadDataSize = 0;
            L_DEBUG("Current size %d", c->size);
            context.worked = 1;
            return MHD_YES;
        }
        else
        {
            L_DEBUG("last call");
            MHD_Result ret = replier->process(connection, url, method, version, context.buffer, context.size);
            context.worked = 1;
            return ret;
        }
    }
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
    L_DEBUG("URL: '%s', method: '%s', upload data size %d", url, method, *uploadDataSize);
    L_DEBUG("Context: %s", *con_cls == NULL ? "NULL" : "Non NULL");

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