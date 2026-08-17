
#include "tmtc.h"

#ifndef TMTC_SOCKET_H
#define TMTC_SOCKET_H

typedef struct tmtc_ctx_socket_s
{
    int port;
} tmtc_ctx_socket_t;

int tmtc_init_socket(void *data, int size);
int tmtc_start_socket(void *data, int size);
int tmtc_send_socket(void *data, int size);
int tmtc_receive_socket(void *data, int size);
int tmtc_stop_socket(void *data, int size);

#endif
