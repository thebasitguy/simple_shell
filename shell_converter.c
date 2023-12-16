#include "shell_headers.h"

/**
 * errstr_toint - converts a string to an integer
 * @s: string to be converted
 *
 * Return: converted number, otherwise -1 on error
 */

int errstr_toint(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}


/**
 * errmsg_tostderr - prints an error message to the stderr
 *
 * @shell_info: parameter and return shell_info struct
 * @estr: string containing specified error type
 *
 * Return: Nothing
 */

void errmsg_tostderr(info_t *shell_info, char *estr)
{
	custom_puts(shell_info->fname);
	custom_puts(": ");
	printdec_tofd(shell_info->line_count, STDERR_FILENO);
	custom_puts(": ");
	custom_puts(shell_info->argv[0]);
	custom_puts(": ");
	custom_puts(estr);
}


/**
 * printdec_tofd - prints a decimal(integer) number to the specified fd
 *
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

int printdec_tofd(int input, int fd)
{
	int (*__putchar)(char) = str_printsingle;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = buffered_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}


/**
 * number_converter - converter function, a clone of shell_checks
 *
 * @num: number to be converted
 * @base: base for conversion
 * @flags: argument flags
 *
 * Return: string
 */

char *number_converter(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}


/**
 * comment_remover - replaces first instance of '#' with '\0'
 * @buf: pointer to the string to modify
 *
 * Return: Always 0;
 */

void comment_remover(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
