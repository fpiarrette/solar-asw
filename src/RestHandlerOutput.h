
#ifndef REST_HANDLER_OUTPUT_H
#define REST_HANDLER_OUTPUT_H

#include "RestHandler.h"

class RestHandlerOutput : public RestHandler
{
public:
    enum MHD_Result handle(
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        char *requestBody,
        int size);

protected:
private:
};

#endif
