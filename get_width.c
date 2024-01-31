#include "main.h"

/**
 * get_width - Calculates the width for printing
 
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Width value.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_s;
	int width = 0;

	for (curr_s = *i + 1; format[curr_s] != '\0'; curr_s++)
	{
		if (is_digit(format[curr_s]))
		{
			width *= 10;
			width += format[curr_s] - '0';
		}
		else if (format[curr_s] == '*')
		{
			curr_s++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_s - 1;

	return width;
}
