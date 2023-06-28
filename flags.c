#include "main.h"

/**
 * get_flags -  calculates active flags
 * @format:  formatted string in which to print the arguments
 * @i:   Take a parameter.
 * Return:  flags representing the active flags.
 */
int get_flags(const char *format, int *i)
{
    /* - + 0 # ' ' */
    /* 1 2 4 8  16 */
    int x, curr_i;
    int flags = 0;
    const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        for (x = 0; FLAGS_CH[x] != '\0'; x++)
            if (format[curr_i] == FLAGS_CH[x])
            {
                flags |= FLAGS_ARR[x];
                break;
            }

        if (FLAGS_CH[x] == 0)
            break;
    }

    *i = curr_i - 1;

    return (flags);
}
