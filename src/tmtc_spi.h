
#include "tmtc.h"

#ifndef TMTC_SPI_H
#define TMTC_SPI_H

typedef struct tmtc_ctx_spi_s
{
    int port;
} tmtc_ctx_spi_t;

int tmtc_init_spi(void *data, int size);
int tmtc_start_spi(void *data, int size);
int tmtc_send_spi(void *data, int size);
int tmtc_receive_spi(void *data, int size);
int tmtc_stop_spi(void *data, int size);

#endif
