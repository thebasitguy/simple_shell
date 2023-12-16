#include "shell_headers.h"

/**
 * str_len - calculates the length of a string
 * @s: the string whose length is to be checked
 *
 * Return: integer length of string
 */

int str_len(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * str_compare - performs lexicogarphic comparison between two strangs
 *
 * @s1: first strang
 * @s2: second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int str_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * str_starts_with - checks if needle starts with haystack
 *
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: address of next character in haystack or NULL
 */

char *str_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * str_concat - concatenates contents of two strings
 *
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */

char *str_concat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
