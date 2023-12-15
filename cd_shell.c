#include "shell_headers.h"

/**
 * exit_shell - exits the shell
 * @shell_info: pointer to a structure
 *
 * Return: -2 to tell the shell to exit
 */

int exit_shell(info_t *shell_info)
{
	int exitcheck;

	if (shell_info->argv[1])
	{
		exitcheck = errstr_toint(shell_info->argv[1]);
		if (exitcheck == -1)
		{
			shell_info->status = 2;
			errmsg_tostderr(shell_info, "Illegal number: ");
			custom_puts(shell_info->argv[1]);
			buffered_putchar('\n');
			return (1);
		}
		shell_info->err_num = errstr_toint(shell_info->argv[1]);
		return (-2);
	}
	shell_info->err_num = -1;
	return (-2);
}

/**
 * cd1_shell - changes the current directory of the shell process
 * @shell_info: pointer to a structure
 *
 * Return: Always 0
 */

int cd1_shell(info_t *shell_info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		str_print("TODO: >>getcwd failure emsg here<<\n");
	if (!shell_info->argv[1])
	{
		dir = env_varvalue(shell_info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = env_varvalue(shell_info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_compare(shell_info->argv[1], "-") == 0)
	{
		if (!env_varvalue(shell_info, "OLDPWD="))
		{
			str_print(s);
			str_printsingle('\n');
			return (1);
		}
		str_print(env_varvalue(shell_info, "OLDPWD=")), str_printsingle('\n');
		chdir_ret =
			chdir((dir = env_varvalue(shell_info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shell_info->argv[1]);
	if (chdir_ret == -1)
	{
		errmsg_tostderr(shell_info, "can't cd to ");
		custom_puts(shell_info->argv[1]), buffered_putchar('\n');
	}
	else
	{
		environ_set(shell_info, "OLDPWD", env_varvalue(shell_info, "PWD="));
		environ_set(shell_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * cd2_shell - changes current directory of the shell process
 * @shell_info: pointer to a structure
 *
 * Return: Always 0
 */

int cd2_shell(info_t *shell_info)
{
	char **arg_array;

	arg_array = shell_info->argv;
	str_print("help call works. Function not yet implemented \n");
	if (0)
		str_print(*arg_array);
	return (0);
}


