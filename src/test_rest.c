#include <stdio.h>
#include <stdlib.h>
#include <microhttpd.h>
#include <string.h>

#define PORT 8888

static enum MHD_Result handler(
    void *cls,
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    const char *upload_data,
    size_t *upload_data_size,
    void **con_cls)
{
    static int dummy;

    if (0 != strcmp(method, "PUT"))
        return MHD_NO;

    /* Primera llamada */
    if (*con_cls == NULL)
    {
        *con_cls = &dummy;
        return MHD_YES;
    }

    /* Llegan datos */
    if (*upload_data_size != 0)
    {
        printf("Recibidos %zu bytes:\n", *upload_data_size);
        fwrite(upload_data, 1, *upload_data_size, stdout);
        printf("\n");

        *upload_data_size = 0;
        return MHD_YES;
    }

    /* Fin de la transferencia */
    const char *msg = "PUT OK\n";

    struct MHD_Response *response =
        MHD_create_response_from_buffer(
            strlen(msg),
            (void *)msg,
            MHD_RESPMEM_PERSISTENT);

    enum MHD_Result ret =
        MHD_queue_response(
            connection,
            MHD_HTTP_OK,
            response);

    MHD_destroy_response(response);

    return ret;
}

int main(void)
{
    struct MHD_Daemon *daemon =
        MHD_start_daemon(
            MHD_USE_INTERNAL_POLLING_THREAD,
            PORT,
            NULL,
            NULL,
            &handler,
            NULL,
            MHD_OPTION_END);

    getchar();

    MHD_stop_daemon(daemon);

    return EXIT_SUCCESS;
}
