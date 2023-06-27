/**
 * get_width - Calculates the width for printing.
 * @frmt: Formatted string in which to print the arguments.
 * @s: List of arguments to be printed.
 * @l: List of arguments.
 *
 * Return: wid.
 */
int get_width(const char *frmt, int *s, va_list l)
{
	int cur_i;
	int wid = 0;

	for (cur_i = *s + 1; frmt[cur_i] != '\0'; cur_i++)
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

	*s = cur_i - 1;

	return wid;
}
