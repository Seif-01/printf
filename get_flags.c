#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: Take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8 16 */
	int s, cur_i;
	int flgs = 0;
	const char FLGS_C[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLGS_AR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (cur_i = *i + 1; format[cur_i] != '\0'; cur_i++)
	{
		for (s = 0; FLGS_C[s] != '\0'; s++)
			if (format[cur_i] == FLGS_C[s])
			{
				flgs |= FLGS_AR[s];
				break;
			}

		if (FLGS_C[s] == 0)
			break;
	}

	*i = cur_i - 1;

	return flgs;
}
