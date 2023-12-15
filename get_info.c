#include "shell_headers.h"

/**
 * info_clear - initializes or clears fields of the info_t structure
 * @shell_info: pointer to a structure
 */

void info_clear(info_t *shell_info)
{
	shell_info->arg = NULL;
	shell_info->argv = NULL;
	shell_info->path = NULL;
	shell_info->argc = 0;
}


/**
 * info_set - initializes or sets info_t structure
 *
 * @shell_info: pointer to a structure
 * @av: argument vector
 */

void info_set(info_t *shell_info, char **av)
{
	int i = 0;

	shell_info->fname = av[0];
	if (shell_info->arg)
	{
		shell_info->argv = str_split1(shell_info->arg, " \t");
		if (!shell_info->argv)
		{

			shell_info->argv = malloc(sizeof(char *) * 2);
			if (shell_info->argv)
			{
				shell_info->argv[0] = str_duplicate(shell_info->arg);
				shell_info->argv[1] = NULL;
			}
		}
		for (i = 0; shell_info->argv && shell_info->argv[i]; i++)
			;
		shell_info->argc = i;

		replace_tstringalias(shell_info);
		replace_tstringvars(shell_info);
	}
}


/**
 * info_free - frees info_t structure fields
 *
 * @shell_info: pointer to a structure
 * @all: frees additional fields if true
 */

void info_free(info_t *shell_info, int all)
{
	str_free(shell_info->argv);
	shell_info->argv = NULL;
	shell_info->path = NULL;
	if (all)
	{
		if (!shell_info->cmd_buf)
			free(shell_info->arg);
		if (shell_info->env)
			free_listnodes(&(shell_info->env));
		if (shell_info->history)
			free_listnodes(&(shell_info->history));
		if (shell_info->alias)
			free_listnodes(&(shell_info->alias));
		str_free(shell_info->environ);
			shell_info->environ = NULL;
		pointer_free((void **)shell_info->cmd_buf);
		if (shell_info->readfd > 2)
			close(shell_info->readfd);
		str_printsingle(BUF_FLUSH);
	}
}

