#include "shell_headers.h"

/**
 * env_variables - prints the current environment variables
 * @shell_info: pointer to a structure
 *
 * Return: Always 0
 */

int env_variables(info_t *shell_info)
{
	print_liststr(shell_info->env);
	return (0);
}


/**
 * env_varvalue - gets the value of an environment variable
 *
 * @shell_info: pointer to a structure
 * @name: environment variable name
 *
 * Return: the value
 */

char *env_varvalue(info_t *shell_info, const char *name)
{
	list_t *node = shell_info->env;
	char *p;

	while (node)
	{
		p = str_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


/**
 * env_set - initializes a new environment variable
 * or modifies an existing one
 *
 * @shell_info: pointer to a structure
 *
 * Return: Always 0
 */

int env_set(info_t *shell_info)
{
	if (shell_info->argc != 3)
	{
		custom_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (environ_set(shell_info, shell_info->argv[1], shell_info->argv[2]))
		return (0);
	return (1);
}


/**
 * env_unset - removes environment variable(s)
 * @shell_info: pointer to a structure
 *
 * Return: Always 0
 */

int env_unset(info_t *shell_info)
{
	int i;

	if (shell_info->argc == 1)
	{
		custom_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= shell_info->argc; i++)
		environ_unset(shell_info, shell_info->argv[i]);

	return (0);
}


/**
 * envlist_populate - populates the environment linked list
 * @shell_info: pointer to a structure
 *
 * Return: Always 0
 */

int envlist_populate(info_t *shell_info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addnode_listend(&node, environ[i], 0);
	shell_info->env = node;
	return (0);
}
