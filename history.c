#include "shell_headers.h"

/**
 * history_filepath - constructs and returns path to the history file
 * @shell_info: pointer to a structure
 *
 * Return: the allocated string containing history file
 */

char *history_filepath(info_t *shell_info)
{
	char *buf, *dir;

	dir = env_varvalue(shell_info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_copy(buf, dir);
	str_concat(buf, "/");
	str_concat(buf, HIST_FILE);
	return (buf);
}


/**
 * writecmd_history - writes the command history to a file
 * @shell_info: pointer to a structure
 *
 * Return: 1 on success, else -1
 */

int writecmd_history(info_t *shell_info)
{
	ssize_t fd;
	char *filename = history_filepath(shell_info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = shell_info->history; node; node = node->next)
	{
		writeto_fd(node->str, fd);
		write_fd('\n', fd);
	}
	write_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}


/**
 * readcmd_history - reads command history from a file
 * @shell_info: pointer to a structure
 *
 * Return: histcount on success, 0 otherwise
 */

int readcmd_history(info_t *shell_info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = history_filepath(shell_info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			addcmd_history(shell_info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		addcmd_history(shell_info, buf + last, linecount++);
	free(buf);
	shell_info->histcount = linecount;
	while (shell_info->histcount-- >= HIST_MAX)
		remove_indexnodes(&(shell_info->history), 0);
	history_numrenew(shell_info);
	return (shell_info->histcount);
}


/**
 * addcmd_history - adds command entry to a history linked list
 *
 * @shell_info: pointer to a structure
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int addcmd_history(info_t *shell_info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (shell_info->history)
		node = shell_info->history;
	addnode_listend(&node, buf, linecount);

	if (!shell_info->history)
		shell_info->history = node;
	return (0);
}


/**
 * history_numrenew - renews numbering of the history linked
 * list after changes
 *
 * @shell_info: pointer to a structure
 *
 * Return: the new histcount
 */
int history_numrenew(info_t *shell_info)
{
	list_t *node = shell_info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (shell_info->histcount = i);
}

