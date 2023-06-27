#include "main.h"

void print_buffer(character buffer[], int *buff_ind);

/**
* _printf - Printf function
* Return: Printed characters.
* @format: format.
*/
int _printf(const character *format, ...)
{
int i, printed = 0, printed_characters = 0;
int flags, width, precision, size, buff_ind = 0;
va_list list;
character buffer[BUFF_SIZE];

if (format == NULL)
return (-1);

va_start(list, format);

for (i = 0; format && format[i] != '\0'; i++)
{
if (format[i] != '%')
{
buffer[buff_ind++] = format[i];
if (buff_ind == BUFF_SIZE)
print_buffer(buffer, &buff_ind);
/* write(1, &format[i], 1);*/
printed_characters++;
}
else
{
print_buffer(buffer, &buff_ind);
flags = get_flags(format, &i);
width = get_width(format, &i, list);
precision = get_precision(format, &i, list);
size = get_size(format, &i);
++i;
printed = handle_print(format, &i, list, buffer,
flags, width, precision, size);
if (printed == -1)
return (-1);
printed_characters += printed;
}
}

print_buffer(buffer, &buff_ind);

va_end(list);

return (printed_characters);
}

/**
* print_buffer - Prints the contents of the buffer if it exist
* @buff_ind: Index at which to add next char, represents the length.
* @buffer: Array of characters
*/
void print_buffer(char buffer[], int *buff_ind)
{
if (*buff_ind > 0)
write(1, &buffer[0], *buff_ind);

*buff_ind = 0;
}
