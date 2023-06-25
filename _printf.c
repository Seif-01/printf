#include <unistd.h>
#include "main.h"

/**
 * _printf - Produces output according to a format
 * @format: The format string
 *
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
        va_list args;
        int printed_chars = 0;
        char buffer[2] = {'\0', '\0'};

        va_start(args, format);

        if (format == NULL)
                return (-1);

        while (*format != '\0')
        {
                if (*format == '%')
                {
                        format++;
                        if (*format == '%')
                                buffer[0] = '%';
                        else if (*format == 'c')
                                buffer[0] = va_arg(args, int);
                        else if (*format == 's')
                                buffer[0] = va_arg(args, char *);
                        else
                                buffer[0] = *format;
                        write(1, buffer, 1);
                        printed_chars++;
                }
                else
                {
                        write(1, format, 1);
                        printed_chars++;
                }
                format++;
        }

        va_end(args);
        return (printed_chars);
}
