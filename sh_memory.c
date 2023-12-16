#include "shell_headers.h"

/**
 * pointer_free - frees a pointer and makes the address NULL
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int pointer_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

