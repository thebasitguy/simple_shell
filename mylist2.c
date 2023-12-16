#include "shell_headers.h"


/**
 * llist_len - determines the length of a linked list
 * @h: pointer to first node of the list
 *
 * Return: size of list
 */

size_t llist_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * llistto_strings - converts a linked list of strings
 * into an array of strings
 *
 * @head: pointer to first node of the list
 *
 * Return: array of strings
 */

char **llistto_strings(list_t *head)
{
	list_t *node = head;
	size_t i = llist_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_copy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_llistelements - prints all elements of a linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t print_llistelements(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		str_print(number_converter(h->num, 10, 0));
		str_printsingle(':');
		str_printsingle(' ');
		str_print(h->str ? h->str : "(nil)");
		str_print("\n");
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * node_nodeprefix - returns node whose string starts
 * with specified prefix
 *
 * @node: pointer to the list head
 * @prefix: string to match as a prefix
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *node_nodeprefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = str_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_nodeindex - gets the index of a specific node
 *
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t get_nodeindex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

