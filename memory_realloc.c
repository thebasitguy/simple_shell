#include "shell_headers.h"

/**
 * mem_filler - fills the memory with a constant byte
 *
 * @s: the pointer to the memory area
 * @b: the byte to fill the memory with
 * @n: the amount of bytes to be filled
 *
 * Return: (s) a pointer to the memory area s
 */

char *mem_filler(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * str_free - frees a string of strings
 * @pp: pointer to string of strings
 */

void str_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * blockmem_realloc - reallocates a block of memory
 * pointed to by ptr
 *
 * @ptr: pointer to previous mallocated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 *
 * Return: pointer to the new block
 */

void *blockmem_realloc(void *ptr, unsigned int old_size,
		unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

