#include "shell_headers.h"

/**
 * is_interactive - checks if shell is in is_interactive mode
 * @shell_info: pointer to a structure
 *
 * Return: 1 if in is_interactive mode, 0 otherwise
 */

int is_interactive(info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->readfd <= 2);
}


/**
 * char_isdelim - checks if character is a delimeter
 *
 * @c: the character to check
 * @delim: the delimeter string
 *
 * Return: 1 if delimeter, 0 if otherwise
 */

int char_isdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}


/**
 *char_isalpha - checks if character is an alphabetic character
 *@c: The character to check
 *
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int char_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 * str_toint - converts a string to an integer
 * @s: string to be converted
 *
 * Return: the converted number, or 0 if no numbers in string
 */

int str_toint(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
