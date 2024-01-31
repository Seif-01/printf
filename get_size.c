#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @s: List of arguments to be printed.
 * Determines the size to cast the argument 
 * Return: size to cast the argument.
 */
int get_size(const char *format, int *s)
{
    int curr_s = *s + 1;
    int size = 0;

    if (format[curr_s] == 'l')
        size = S_LONG;
    else if (format[curr_s] == 'h')
        size = S_SHORT;

    if (size == 0)
        *s = curr_s - 1;
    else
        *s = curr_s;

    return size;
}
