
#ifndef REST_HANDLER_STATISTICS_H
#define REST_HANDLER_STATISTICS_H

#include "RestHandler.h"

class RestHandlerStatistics : public RestHandler
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
