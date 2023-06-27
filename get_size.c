#include "main.h"


/**
*get_size -  calculates the size to cast the argument
*@format:  formatted string in which to print the arguments
*@s:  list of arguments to be printed.
*
*Return:  size to cast the argument.
*/
int get_precision(const char *format, int *s, va_list list)
{
    int curr_s = *s + 1;
    int precision = -1;

    if (format[curr_s] != '.')
        return (precision);

    precision = 0;

    for (curr_s += 1; format[curr_s] != '\0'; curr_s++)
    {
        if (is_digit(format[curr_s]))
        {
            precision *= 10;
            precision += format[curr_s] - '0';
        }
        else if (format[curr_s] == '*')
        {
            curr_s++;
            precision = va_arg(list, int);
            break;
        }
        else
            break;
    }

    *s = curr_s - 1;

    return (precision);
}
