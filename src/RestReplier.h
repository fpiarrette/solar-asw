
#ifndef REST_REPLIER_H
#define REST_REPLIER_H

#include "microhttpd.h"

class RestReplier
{
public:
    enum MHD_Result process(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

    MHD_Result reply(struct MHD_Connection *connection, int code, const char *body, size_t size);

protected:
    enum MHD_Result processStatus(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

    enum MHD_Result processStatistics(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

    enum MHD_Result processConfig(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

    enum MHD_Result processNotFound(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

    enum MHD_Result replyError(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        int code,
        const char *message);

private:
};

#endif
