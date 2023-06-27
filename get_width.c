#include "main.h"

/**
 * get_width - Calculates the width for printing.
 * @frmt: Formatted string in which to print the arguments.
 * @ji: List of arguments to be printed.
 * @l: List of arguments.
 *
 * Return: wid.
 */
int get_width(const char *frmt, int *ji, va_list l)
{
	int cur_i;
	int wid = 0;

	for (cur_i = *ji + 1; frmt[cur_i] != '\0'; cur_i++)
	{
		if (is_digit(frmt[cur_i]))
		{
			wid *= 10;
			wid += frmt[cur_i] - '0';
		}
		else if (frmt[cur_i] == '*')
		{
			cur_i++;
			wid = va_arg(l, int);
			break;
		}
		else
			break;
	}

	*ji = cur_i - 1;

	return wid;
}
