#include "shell_headers.h"

/**
 * environ_copy - returns a copy of string array of our environment
 * @shell_info: pointer to structure
 *
 * Return: Always 0
 */

char **environ_copy(info_t *shell_info)
{
	if (!shell_info->environ || shell_info->env_changed)
	{
		shell_info->environ = llistto_strings(shell_info->env);
		shell_info->env_changed = 0;
	}

	return (shell_info->environ);
}


/**
 * environ_unset - Removes an environment variable
 *
 * @shell_info: pointer to structure
 * @var: the string environment variable property
 *
 * Return: 1 on delete, 0 otherwise
 */

int environ_unset(info_t *shell_info, char *var)
{
	list_t *node = shell_info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			shell_info->env_changed = remove_indexnodes(&(shell_info->env), i);
			i = 0;
			node = shell_info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shell_info->env_changed);
}


/**
 * environ_set - initializes a new environment variable,
 * or modifies an existing one
 *
 * @shell_info: pointer to structure
 * @var: the string env var property
 * @value: the string env var value
 *
 * Return: 0 on success, 1 on failure
 */

int environ_set(info_t *shell_info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_copy(buf, var);
	str_concat(buf, "=");
	str_concat(buf, value);
	node = shell_info->env;
	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			shell_info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addnode_listend(&(shell_info->env), buf, 0);
	free(buf);
	shell_info->env_changed = 1;
	return (0);
}

