
#ifndef TASK_REST_H
#define TASK_REST_H

#include "Scheduller.h"
#include "microhttpd.h"

#include "RestHandler.h"
#include "CircularBuffer.h"

#include <iostream>
#include <string>
#include <unordered_map>

typedef struct
{
    CircularBuffer<char, 8 * 1024> circular;
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
    void addHandler(const char *uri, RestHandler *h);

protected:
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
    static std::unordered_map<std::string, RestHandler *> handlers;
};

#endif
