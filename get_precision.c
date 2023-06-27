#include "main.h"

/**
 * get_precision - Calculates the precision for printing.
 * @frmt: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @li: List of arguments.
 *
 * Return: Precision.
 */
int get_precs(const char *frmt, int *i, va_list li)
{
	int cur_i = *i + 1;
	int precs = -1;

	if (frmt[cur_i] != '.')
		return precs;

	precs = 0;

	for (cur_i += 1; frmt[cur_i] != '\0'; cur_i++)
	{
		if (is_digit(frmt[cur_i]))
		{
			precs *= 10;
			precs += frmt[cur_i] - '0';
		}
		else if (frmt[cur_i] == '*')
		{
			cur_i++;
			precs = va_arg(li, int);
			break;
		}
		else
			break;
	}

	*i = cur_i - 1;

	return precs;
}
