
#ifndef TASK_REST_H
#define TASK_REST_H

#include "Scheduller.h"
#include "microhttpd.h"

typedef struct
{
    char buffer[8 * 1024];
    size_t size;
    int worked;
} http_context_t;

class TaskRest : public Scheduller::Task
{
public:
    TaskRest();
    ~TaskRest()
    {
        stop();
    }
    const char *getName(void);
    void prepare(void);
    Scheduller::Task::Result run(long int time);
    void stop(void);

protected:
    static MHD_Result reply(struct MHD_Connection *connection, int code, const char *body, size_t size);
    static enum MHD_Result requestHandler(
        void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *uploadData,
        size_t *uploadDataSize,
        void **con_cls);
    static enum MHD_Result requestHandlerSingle(
        void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *uploadData,
        size_t *uploadDataSize,
        void **con_cls);
    static enum MHD_Result requestHandlerParts(
        void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *uploadData,
        size_t *uploadDataSize,
        void **con_cls);

private:
    struct MHD_Daemon *daemon;
    static http_context_t context;
    int port;
};

#endif
