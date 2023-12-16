#include "shell_headers.h"

/**
 * str_copy - copies a string from src to dest
 *
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to the destination buffer
 */

char *str_copy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * str_duplicate - duplicates an input string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *str_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *str_print - prints the input string
 *@str: string to be printed
 *
 * Return: Nothing
 */

void str_print(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		str_printsingle(str[i]);
		i++;
	}
}

/**
 * str_printsingle - writes a single character c to stdout
 * @c: the character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int str_printsingle(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
