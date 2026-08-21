
#ifndef UTILS_H
#define UTILS_H

void utils_sleep(unsigned int ms);

long int utils_curr_time_in_ms(void);

#define xstr(a) str(a)
#define str(a) #a

#endif
