
#ifndef REST_HANDLER_H
#define REST_HANDLER_H

#include "microhttpd.h"

class RestHandler
{
public:
    virtual enum MHD_Result handle(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size) = 0;

    static MHD_Result reply(struct MHD_Connection *connection, int code, const char *body, size_t size);
    static MHD_Result replyEmpty(struct MHD_Connection *connection, int code);

protected:
private:
};

#endif
