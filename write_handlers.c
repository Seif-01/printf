#include "main.h"

/************************* WRITE HANDLE *************************/
/**
* handle_write_char - Prints a string
* @c: char types.
* @buffer: Buffer array to handle print
* @flags:  Calculates active flags.
* @width: get width.
* @precision: precision specifier
* @size: Size specifier
*
* Return: Number of chars printed.
*/
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
int s = 0;
char padd = ' ';

UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
padd = '0';

buffer[s++] = c;
buffer[s] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (s = 0; s < width - 1; s++)
buffer[BUFF_SIZE - s - 2] = padd;

if (flags & F_MINUS)
return (write(1, &buffer[0], 1) +
write(1, &buffer[BUFF_SIZE - s - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - s - 1], width - 1) +
write(1, &buffer[0], 1));
}

return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
* write_number - Prints a string
* @is_negative: Lista of arguments
* @ind: char types.
* @buffer: Buffer array to handle print
* @flags:  Calculates active flags
* @width: get width.
* @precision: precision specifier
* @size: Size specifier
*
* Return: Number of chars printed.
*/
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padd = ' ', extra_ch = 0;

UNUSED(size);

if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';

return (write_num(ind, buffer, flags, width, precision,
length, padd, extra_ch));
}

/**
* write_num - Write a number using a bufffer
* @ind: Index at which the number starts on the buffer
* @buffer: Buffer
* @flags: Flags
* @width: width
* @prec: Precision specifier
* @length: Number length
* @padd: Pading char
* @extra_c: Extra char
*
* Return: Number of printed chars.
*/
int write_num(int ind, char buffer[],
int flags, int width, int prec,
int length, char padd, char extra_c)
{
int s, padd_start = 1;

if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0); /* printf(".0d", 0)  no char is printed */
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
if (prec > 0 && prec < length)
padd = ' ';
while (prec > length)
buffer[BUFF_SIZE - ++length] = '0';
if (flags & (F_PLUS | F_SPACE | F_HASH))
padd_start = 0;
for (s = ind; s < BUFF_SIZE - length - padd_start; s++)
buffer[s] = padd;
if (padd_start == 0)
buffer[s] = extra_c;
for (s = BUFF_SIZE - 1; s >= ind + length; s--)
buffer[s] = '0' + ABS(buffer[s]);
return (write(1, &buffer[ind], BUFF_SIZE - ind));
}

/**
* write_unsgnd - Write an unsigned number
* @is_negative: Number indicating if the number is negative.
* @ind: Index at which the number starts on the buffer
* @buffer: Buffer
* @flags: Flags
* @width: Width
* @precision: Precision specifier
* @size: Size specifier
*
* Return: Number of written chars.
*/
int write_unsgnd(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
UNUSED(is_negative);
return (write_num(ind, buffer, flags, width, precision,
size, ' ', 0));
}

/**
* write_pointer - Write a memory address
* @buffer: Buffer
* @ind: Index at which the number starts on the buffer
* @length: Length of the number
* @width: Width specifier
* @flags: Flags specifier
* @padd: Padding char
* @extra_c: Extra char
* @padd_start: Index at which padding should start
*
* Return: Number of written chars.
*/
int write_pointer(char buffer[], int ind, int length,
int width, int flags, char padd, char extra_c, int padd_start)
{
int s;

if (flags & F_MINUS)
{
for (s = ind; s < BUFF_SIZE - length; s++)
buffer[s] = '0';
buffer[s++] = 'x';
buffer[s++] = '0';
for (; s < BUFF_SIZE - width; s++)
buffer[s] = padd;
if (padd_start == 0)
buffer[s++] = extra_c;
return (write(1, &buffer[ind], BUFF_SIZE - ind));
}
if (flags & F_ZERO)
{
buffer[ind] = '0';
buffer[ind + 1] = 'x';
for (s = ind + 2; s < BUFF_SIZE - width + 2; s++)
buffer[s] = '0';
if (padd_start == 0)
buffer[s++] = extra_c;
for (; s < BUFF_SIZE - length; s++)
buffer[s] = padd;
return (write(1, &buffer[ind], BUFF_SIZE - ind));
}
for (s = ind; s < BUFF_SIZE - width - 2; s++)
buffer[s] = padd;
if (padd_start == 0)
buffer[s++] = extra_c;
buffer[s++] = '0';
buffer[s++] = 'x';
for (; s < BUFF_SIZE - length; s++)
buffer[s] = '0';
return (write(1, &buffer[ind], BUFF_SIZE - ind));
}
