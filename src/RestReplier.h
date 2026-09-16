
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
        const char *version);

    MHD_Result reply(struct MHD_Connection *connection, int code, const char *body, size_t size);

protected:
private:
};

#endif
