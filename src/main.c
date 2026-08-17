#include "tmtc_socket.h"
#include "tmtc_spi.h"

#include <signal.h>

tmtc_ctx_socket_t tmtc_ctx_socket;
tmtc_ctx_spi_t tmtc_ctx_spi;

int main(void) {

    /* Initialization */
    tmtc_ctx_socket.port = 2000;
    tmtc_init_socket(&tmtc_ctx_socket, 0);
    tmtc_init_spi(&tmtc_ctx_spi, 0);

    /* Main loop */


    return 0;
}
