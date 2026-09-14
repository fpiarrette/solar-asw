#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_prefix(const char *prefix, const char *str)
{
    return strncmp(prefix, str, strlen(prefix)) == 0;
}

int str_2_hex(char *hex, char *str, int *size)
{
    char b[3];
    int v, l, s, n;

    l = strlen(str);

    if ((l % 1) != 0)
    {
        return -1;
    }

    s = 0;
    n = 0;

    if (check_prefix("0x", str))
    {
        /* in case 0x prefix */
        n = 2;
    }

    for (; n < l; n += 2, s++)
    {
        b[0] = str[n + 0];
        b[1] = str[n + 1];
        b[2] = 0;

        if (sscanf(b, "%02x", &v) != 1)
        {
            return -2;
        }

        hex[s] = v;
    }

    *size = s;

    return 0;
}

int hex_2_str(char *str, char *hex, int size)
{
    int r;
    int w;

    w = 0;

    sprintf(&str[w * 2], "0x");

    for (w = 1, r = 0; r < size; r++, w++)
    {
        sprintf(&str[w * 2], "%02x", hex[r]);
    }

    str[w * 2] = 0;

    return 0;
}
