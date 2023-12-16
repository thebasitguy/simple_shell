#include "shell_headers.h"

/**
 * is_command - checks if a file is an executable command
 *
 * @shell_info: pointer to a structure
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int is_command(info_t *shell_info, char *path)
{
	struct stat st;

	(void)shell_info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_characters - duplicates characters
 *
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */

char *dup_characters(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * locate_path - searches for the cmd in the PATH string
 *
 * @shell_info: pointer to a structure
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found, otherwise NULL
 */

char *locate_path(info_t *shell_info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && str_starts_with(cmd, "./"))
	{
		if (is_command(shell_info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_characters(pathstr, curr_pos, i);
			if (!*path)
				str_concat(path, cmd);
			else
			{
				str_concat(path, "/");
				str_concat(path, cmd);
			}
			if (is_command(shell_info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
