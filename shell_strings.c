#include "shell_headers.h"

/**
 * str_ncopy - copies a string
 *
 * @src: the source string
 * @dest: the destination string to be copied to
 * @n: the amount of characters to be copied
 *
 * Return: pointer to the destination string
 */

char *str_ncopy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * str_nconcat - concatenates two strings
 *
 * @dest: the first string
 * @src: the second string
 * @n: the maximum amount of bytes to be used
 *
 *Return: pointer to the destination string
 */

char *str_nconcat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * str_findchar - finds a character in a string
 *
 * @s: the string to be parsed
 * @c: the character to look for
 *
 * Return: (s) a pointer to the memory area s
 */

char *str_findchar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
