
#ifndef SETUP_H
#define SETUP_H

#include "Alarms.h"

/* **************************************************************************************** */
/* custom GPIOs                                                                             */
/* **************************************************************************************** */
/* GPIO error line */
#define SETUP_GPIO_ERROR_PORT (3)
#define SETUP_GPIO_ERROR_LINE (28)
/* GPIO warning line */
#define SETUP_GPIO_WARNING_PORT (3)
#define SETUP_GPIO_WARNING_LINE (28)
/* GPIO SPI vs TCP MUX line */
#define SETUP_GPIO_MUX_PORT (3)
#define SETUP_GPIO_MUX_LINE (29)

/* **************************************************************************************** */
/* custom alamrs                                                                            */
/* **************************************************************************************** */
#define SETUP_ALARM_TENTH_SECOND (ALARM_DEF_10)
#define SETUP_ALARM_SECOND (ALARM_DEF_11)
#define SETUP_ALARM_HUNDRED_MS (ALARM_DEF_12)

#define SETUP_ALARM_ERROR (ALARM_DEF_20)
#define SETUP_ALARM_WARNING (ALARM_DEF_21)

#define SETUP_ALARM_KILL (ALARM_DEF_27)
#define SETUP_ALARM_STOP (ALARM_DEF_28)
#define SETUP_ALARM_RESUME (ALARM_DEF_29)

#define SETUP_ALARM_INPUT_CHANNEL_0 (ALARM_DEF_17)
#define SETUP_ALARM_INPUT_CHANNEL_1 (ALARM_DEF_18)

#endif
