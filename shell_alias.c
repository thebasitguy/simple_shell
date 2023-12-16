i#include "shell_headers.h"

/**
 * show_history - shows the history list, displaying each command
 * with line numbers starting from 0
 *
 * @shell_info: pointer to a structure
 *
 *  Return: Always 0
 */

int show_history(info_t *shell_info)
{
	print_llistelements(shell_info->history);
	return (0);
}

/**
 * remove_alias - unsets alias by removing it
 * from the alias list
 *
 * @shell_info: pointer to a structure
 * @str: string alias to unset
 *
 * Return: 0 on success, 1 on error
 */

int remove_alias(info_t *shell_info, char *str)
{
	char *p, c;
	int ret;

	p = str_findchar(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_indexnodes(&(shell_info->alias),
		get_nodeindex(shell_info->alias, node_nodeprefix(shell_info->alias,
				str, -1)));
	*p = c;
	return (ret);
}

/**
 * add_alias - sets alias by adding it to the alias list
 *
 * @shell_info: pointer to a structure
 * @str: the string alias to set
 *
 * Return: 0 on success, 1 on error
 */

int add_alias(info_t *shell_info, char *str)
{
	char *p;

	p = str_findchar(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(shell_info, str));

	remove_alias(shell_info, str);
	return (addnode_listend(&(shell_info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: pointer to a node in the alias list
 *
 * Return: 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = str_findchar(node->str, '=');
		for (a = node->str; a <= p; a++)
			str_printsingle(*a);
		str_printsingle('\'');
		str_print(p + 1);
		str_print("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_mimic - mimics the alias built-in command
 * @shell_info: pointer to a structure
 *
 * Return: Always 0
 */

int alias_mimic(info_t *shell_info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (shell_info->argc == 1)
	{
		node = shell_info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shell_info->argv[i]; i++)
	{
		p = str_findchar(shell_info->argv[i], '=');
		if (p)
			add_alias(shell_info, shell_info->argv[i]);
		else
			print_alias(node_nodeprefix(shell_info->alias, shell_info->argv[i], '='));
	}

	return (0);
}

