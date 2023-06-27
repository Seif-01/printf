#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *s,
va_list li, char buff[], int flgs, int wid, int precs, int sz);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int print_char(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);
int print_string(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);
int print_percent(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);

/* Functions to print numbers */
int print_int(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);
int print_binary(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);
int print_unsigned(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);
int print_octal(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);
int print_hexadecimal(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);
int print_hexa_upper(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);

int print_hexa(va_list types, char map_to[],
char buff[], int flgs, char FLGS_C, int wid, int precs, int sz);

/* Function to print non printable characters */
int print_non_printable(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);

/* Function to print memory address */
int print_pointer(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);

/* Functions to handle other specifiers */
int get_flags(const char *frmt, int *s);
int get_width(const char *frmt, int *s, va_list l);
int get_precision(const char *frmt, int *s, va_list l);
int get_size(const char *frmt, int *s);

/* Function to print string in reverse */
int print_reverse(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);

/* Function to print a string in rot 13 */
int print_rot13string(va_list types, char buff[],
	int flgs, int wid, int precs, int sz);

/* Width handler */
int handle_write_char(char c, char buff[],
	int flgs, int wid, int precs, int sz);
int write_number(int is_positive, int ind, char buff[],
	int flgs, int wid, int precs, int sz);
int write_num(int ind, char bff[], int flgs, int wid, int precs,
	int l, char padd, char extra_c);
int write_pointer(char buff[], int ind, int l,
	int wid, int flgs, char pad, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
	char buff[],
	int flgs, int wid, int precs, int sz);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int sz);
long int convert_size_unsgnd(unsigned long int num, int sz);

#endif /* MAIN_H */
