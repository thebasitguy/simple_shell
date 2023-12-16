#include "shell_headers.h"

/**
 *custom_puts - prints input string to stderr
 * @str: pointer to string to be printed
 *
 * Return: Nothing
 */

void custom_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		buffered_putchar(str[i]);
		i++;
	}
}


/**
 * buffered_putchar - writes the character to stderr
 * @c: the character to print
 *
 * Return: On success 1, or -1 on error
 * and errno is set appropriately
 */

int buffered_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}


/**
 * write_fd - writes the character to a specified fd
 *
 * @c: the character to print
 * @fd: the file descriptor to write to
 *
 * Return: On success 1, or -1 on error
 * and errno is set appropriately
 */

int write_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}


/**
 *writeto_fd - prints the input string to a specified fd
 *
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */

int writeto_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_fd(*str++, fd);
	}
	return (i);
}
