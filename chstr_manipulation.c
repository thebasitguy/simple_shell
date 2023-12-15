#include "shell_headers.h"

/**
 * isbufchar_chain - checks if current character in buffer is a chain delimeter
 *
 * @shell_info: pointer to a structure
 * @buf: the character buffer
 * @p: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int isbufchar_chain(info_t *shell_info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		shell_info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		shell_info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		shell_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


/**
 * chain_checker - checks if we should continue chaining
 * based on the last status
 *
 * @shell_info: pointer to a structure
 * @buf: the character buffer
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: void
 */

void chain_checker(info_t *shell_info, char *buf,
		size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (shell_info->cmd_buf_type == CMD_AND)
	{
		if (shell_info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (shell_info->cmd_buf_type == CMD_OR)
	{
		if (!shell_info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}


/**
 * replace_tstringalias - replaces an alias in the tokenized string
 * @shell_info: pointer to a structure
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_tstringalias(info_t *shell_info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_nodeprefix(shell_info->alias, shell_info->argv[0], '=');
		if (!node)
			return (0);
		free(shell_info->argv[0]);
		p = str_findchar(node->str, '=');
		if (!p)
			return (0);
		p = str_duplicate(p + 1);
		if (!p)
			return (0);
		shell_info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_tstringvars - replaces vars in the tokenized string
 * @shell_info: pointer to a structure
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_tstringvars(info_t *shell_info)
{
	int i = 0;
	list_t *node;

	for (i = 0; shell_info->argv[i]; i++)
	{
		if (shell_info->argv[i][0] != '$' || !shell_info->argv[i][1])
			continue;

		if (!str_compare(shell_info->argv[i], "$?"))
		{
			replace_string(&(shell_info->argv[i]),
				str_duplicate(number_converter(shell_info->status, 10, 0)));
			continue;
		}
		if (!str_compare(shell_info->argv[i], "$$"))
		{
			replace_string(&(shell_info->argv[i]),
				str_duplicate(number_converter(getpid(), 10, 0)));
			continue;
		}
		node = node_nodeprefix(shell_info->env, &shell_info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(shell_info->argv[i]),
				str_duplicate(str_findchar(node->str, '=') + 1));
			continue;
		}
		replace_string(&shell_info->argv[i], str_duplicate(""));

	}
	return (0);
}


/**
 * replace_string - replaces string
 *
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

