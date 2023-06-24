#include <unistd.h>
#include <stdarg.h>

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[1024];
    int i = 0;

    va_start(args, format);

    while (format && format[i])
    {
        if (format[i] != '%')
        {
            buffer[count++] = format[i++];
            continue;
        }

        i++;

        if (format[i] == '\0')
            break;

        if (format[i] == '%')
        {
            buffer[count++] = '%';
            i++;
            continue;
        }

        if (format[i] == 'c')
        {
            int c = va_arg(args, int);
            buffer[count++] = c;
        }
        else if (format[i] == 's')
        {
            char *s = va_arg(args, char*);
            while (*s)
            {
                buffer[count++] = *s++;
            }
        }

        i++;
    }

    write(1, buffer, count);

    va_end(args);

    return count;
}
