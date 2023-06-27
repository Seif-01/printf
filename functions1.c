#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable.
 * @types: List of arguments.
 * @buff: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buff[],
int flags, int width, int precision, int size)
{
char extra_c = 0, pad = ' ';
int ind = BUFF_SIZE - 2, l = 2, padd_start = 1; /* l=2, for '0x' */
unsigned long num_addrs;
char map_to[] = "0123456789abcdef";
void *addrs = va_arg(types, void *);

UNUSED(width);
UNUSED(size);

if (addrs == NULL)
return (write(1, "(nil)", 5));

buff[BUFF_SIZE - 1] = '\0';
UNUSED(precision);

num_addrs = (unsigned long)addrs;

while (num_addrs > 0)
{
buff[ind--] = map_to[num_addrs % 16];
num_addrs /= 16;
l++;
}

if ((flags & F_ZERO) && !(flags & F_MINUS))
pad = '0';
if (flags & F_PLUS)
extra_c = '+', l++;
else if (flags & F_SPACE)
extra_c = ' ', l++;

ind++;

/* return (write(1, &buff[s], BUFF_SIZE - s - 1)); */
return (write_pointer(buff, ind, l,
width, flags, pad, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ASCII codes in hexa of non-printable chars.
 * @types: List of arguments.
 * @buff: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of chars printed.
 */
int print_non_printable(va_list types, char buff[],
int flags, int width, int precision, int size)
{
int s = 0, offs = 0;
char *str = va_arg(types, char *);

UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

if (str == NULL)
return (write(1, "(null)", 6));

while (str[s] != '\0')
{
if (is_printable(str[s]))
buff[s + offs] = str[s];
else
offs += append_hexa_code(str[s], buff, s + offs);

s++;
}

buff[s + offs] = '\0';
return (write(1, buff, s + offs));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: List of arguments.
 * @buff: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of chars printed.
 */
int print_reverse(va_list types, char buff[],
int flags, int width, int precision, int size)
{
char *str;
int s, count = 0;

UNUSED(buff);
UNUSED(flags);
UNUSED(width);
UNUSED(size);

str = va_arg(types, char *);

if (str == NULL)
{
UNUSED(precision);

str = ")Null(";
}
for (s = 0; str[s]; s++)
;

for (s = s - 1; s >= 0; s--)
{
char z = str[s];

write(1, &z, 1);
count++;
}
return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in ROT13.
 * @types: List of arguments.
 * @buff: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of chars printed.
 */
int print_rot13string(va_list types, char buff[],
int flags, int width, int precision, int size)
{
char x;
char *str;
unsigned int s, j;
int count = 0;
char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

str = va_arg(types, char *);
UNUSED(buff);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

if (str == NULL)
str = "(AHYY)";
for (s = 0; str[s]; s++)
{
for (j = 0; in[j]; j++)
{
if (in[j] == str[s])
{
x = out[j];
write(1, &x, 1);
count++;
break;
}
}
if (!in[j])
{
x = str[s];
write(1, &x, 1);
count++;
}
}
return (count);
}

