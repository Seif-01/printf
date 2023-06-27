#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @f: format.
 * Return: Printed chars.
 */
int _printf(const char *f, ...)
{
	int s, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list l;
	char buffer[BUFF_SIZE];

	if (f == NULL)
		return (-1);

	va_start(l, f);

	for (s = 0; f && f[s] != '\0'; s++)
	{
		if (f[s] != '%')
		{
			buffer[buff_ind++] = f[s];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &f[s], 1); */
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(f, &s);
			width = get_width(f, &s, l);
			precision = get_precision(f, &s, l);
			size = get_size(f, &s);
			++s;
			printed = handle_print(f, &s, l, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(l);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
