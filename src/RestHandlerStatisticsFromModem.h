
#ifndef REST_HANDLER_STATISTICS_FROM_MODEM_H
#define REST_HANDLER_STATISTICS_FROM_MODEM_H

#include "RestHandler.h"

class RestHandlerStatisticsFromModem : public RestHandler
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
