#include "utils.h"
#include "tmtc_socket.h"
#include "tmtc_spi.h"

#include <signal.h>
#include <stdlib.h>

tmtc_ctx_socket_t tmtc_ctx_socket;
tmtc_ctx_spi_t tmtc_ctx_spi;

int stopped;
int terminated;

static void signal_handler(int signal) {
    switch (signal) {
        case SIGINT:
        terminated = 1;
        break;
        case SIGTSTP:
        stopped = 1;
        break;
        case SIGCONT:
        stopped = 0;
        break;
        default:
        break;
    }
}

int main(void) {

    /* Initialization */
    tmtc_ctx_socket.port = 2000;
    tmtc_init_socket(&tmtc_ctx_socket, 0);
    tmtc_init_spi(&tmtc_ctx_spi, 0);

    struct sigaction psa;
    psa.sa_handler = signal_handler;
    sigaction(SIGINT, &psa, NULL);
    sigaction(SIGTSTP, &psa, NULL);
    sigaction(SIGCONT, &psa, NULL);

    /* Main loop */
    while (!terminated) {
        if (!stopped) {
            /* do the job */
        }
        else {
            /* sleep for 100mS */
            utils_sleep(100);
        }
    }

    /* stop/deallocate componets */
    tmtc_stop_socket(&tmtc_ctx_socket, 0);
    tmtc_stop_spi(&tmtc_ctx_spi, 0);

    return 0;
}
