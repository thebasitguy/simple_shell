#include "shell_headers.h"

/**
 * hsh - main shell loop
 *
 * @shell_info: parameter & return shell_info structure
 * @av: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *shell_info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_clear(shell_info);
		if (is_interactive(shell_info))
			str_print("$ ");
		buffered_putchar(BUF_FLUSH);
		r = line_nonline(shell_info);
		if (r != -1)
		{
			info_set(shell_info, av);
			builtin_ret = locate_builtin(shell_info);
			if (builtin_ret == -1)
				locate_command(shell_info);
		}
		else if (is_interactive(shell_info))
			str_printsingle('\n');
		info_free(shell_info, 0);
	}
	writecmd_history(shell_info);
	info_free(shell_info, 1);
	if (!is_interactive(shell_info) && shell_info->status)
		exit(shell_info->status);
	if (builtin_ret == -2)
	{
		if (shell_info->err_num == -1)
			exit(shell_info->status);
		exit(shell_info->err_num);
	}
	return (builtin_ret);
}

/**
 * locate_builtin - searches for a built-in command
 * @shell_info: pointer to a structure
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */

int locate_builtin(info_t *shell_info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", env_variables},
		{"help", cd2_shell},
		{"history", show_history},
		{"setenv", env_set},
		{"unsetenv", env_unset},
		{"cd", cd1_shell},
		{"alias", alias_mimic},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_compare(shell_info->argv[0], builtintbl[i].type) == 0)
		{
			shell_info->line_count++;
			built_in_ret = builtintbl[i].func(shell_info);
			break;
		}
	return (built_in_ret);
}

/**
 * locate_command - finds the full path of a command in PATH
 * @shell_info: pointer to a structure
 *
 * Return: void
 */

void locate_command(info_t *shell_info)
{
	char *path = NULL;
	int i, k;

	shell_info->path = shell_info->argv[0];
	if (shell_info->linecount_flag == 1)
	{
		shell_info->line_count++;
		shell_info->linecount_flag = 0;
	}
	for (i = 0, k = 0; shell_info->arg[i]; i++)
		if (!char_isdelim(shell_info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = locate_path(shell_info, env_varvalue(shell_info, "PATH="),
			shell_info->argv[0]);
	if (path)
	{
		shell_info->path = path;
		fork_command(shell_info);
	}
	else
	{
		if ((is_interactive(shell_info) || env_varvalue(shell_info, "PATH=")
			|| shell_info->argv[0][0] == '/') && is_command
				(shell_info, shell_info->argv[0]))
			fork_command(shell_info);
		else if (*(shell_info->arg) != '\n')
		{
			shell_info->status = 127;
			errmsg_tostderr(shell_info, "not found\n");
		}
	}
}

/**
 * fork_command - forks a child process using
 * an execve thread to run cmd
 * @shell_info: pointer to a structure
 *
 * Return: void
 */

void fork_command(info_t *shell_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shell_info->path, shell_info->argv,
					environ_copy(shell_info)) == -1)
		{
			info_free(shell_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shell_info->status));
		if (WIFEXITED(shell_info->status))
		{
			shell_info->status = WEXITSTATUS(shell_info->status);
			if (shell_info->status == 126)
				errmsg_tostderr(shell_info, "Permission denied\n");
		}
	}
}

