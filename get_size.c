#include "main.h"

/**
 * get_size - Calculates the size to cast the argument.
 * @frmt: Formatted string in which to print the arguments.
 * @s: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *frmt, int *s)
{
    int cur_i = *s + 1;
    int sz = 0;

    if (frmt[cur_i] == 'l')
        sz = S_LONG;
    else if (frmt[cur_i] == 'h')
        sz = S_SHORT;

    if (sz == 0)
        *s = cur_i - 1;
    else
        *s = cur_i;

    return sz;
}
