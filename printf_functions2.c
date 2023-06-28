#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - prints the value of a pointer variable
 * @types:  list a of arguments
 * @buffer:  buffer array to handle print
 * @width: get width
 * @precision: precision specification
 * @flags:  calculates active flags
 * @size: size specifier
 * Return: number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char extra_c = 0, padd = ' ';
    int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
    unsigned long num_addrs;
    char map_to[] = "0123456789abcdef";
    void *addrs = va_arg(types, void *);

    UNUSED(width);
    UNUSED(size);

    if (addrs == NULL)
        return (write(1, "(nil)", 5));

    buffer[BUFF_SIZE - 1] = '\0';
    UNUSED(precision);

    num_addrs = (unsigned long)addrs;

    while (num_addrs > 0)
    {
        buffer[ind--] = map_to[num_addrs % 16];
        num_addrs /= 16;
        length++;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';
    if (flags & F_PLUS)
        extra_c = '+', length++;
    else if (flags & F_SPACE)
        extra_c = ' ', length++;

    ind++;

    return (write_pointer(buffer, ind, length,
        width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ASCII codes in hexa of non-printable chars
 * @types:  list of arguments
 * @buffer: buffer array to handle print
 * @width: get width
 * @precision: precision specification
 * @flags: calculates active flags
 * @size: size specifier
 * Return: number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    int s = 0, offset = 0;
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
            buffer[s + offset] = str[s];
        else
            offset += append_hexa_code(str[s], buffer, s + offset);

        s++;
    }

    buffer[s + offset] = '\0';

    return (write(1, buffer, s + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - prints reverse string.
 * @types:  list of arguments
 * @buffer:  buffer array to handle print
 * @width:  get width
 * @precision:  precision specification
 * @flags:  calculates active flags
 * @size:  size specifier
 * Return:  numbers of chars printed
 */
int print_reverse(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char *str;
    int s, count = 0;

    UNUSED(buffer);
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
 * print_rot13string -  print a string in ROT13.
 * @types:  list of arguments
 * @buffer:  buffer array to handle print
 * @precision:  precision specification
 * @flags:  calculates active flags
 * @size:  size specifier
 * Return:  numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char x;
    char *str;
    unsigned int s, j;
    int count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    str = va_arg(types, char *);
    UNUSED(buffer);
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
