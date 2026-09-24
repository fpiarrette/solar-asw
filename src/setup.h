
#ifndef SETUP_H
#define SETUP_H

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
#define SETUP_ALARM_TENTH_SECOND (10)
#define SETUP_ALARM_SECOND (11)
#define SETUP_ALARM_HUNDRED_MS (12)

#define SETUP_ALARM_ERROR (20)
#define SETUP_ALARM_WARNING (21)

#define SETUP_ALARM_KILL (27)
#define SETUP_ALARM_STOP (28)
#define SETUP_ALARM_RESUME (29)

#endif
