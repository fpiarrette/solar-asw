
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
    MHD_Result replyEmpty(struct MHD_Connection *connection, int code);

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

    enum MHD_Result processInput(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

private:
};

#endif
