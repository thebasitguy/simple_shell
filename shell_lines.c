#include "shell_headers.h"

/**
 * buf_chcommands - buffers chained commands
 *
 * @shell_info: pointer to a structure
 * @buf: address of a pointer to a buffer (string)
 * @len: address of a variable to store the length of the buffer
 *
 * Return: number of bytes read
 */

ssize_t buf_chcommands(info_t *shell_info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, ctrlc_blocker);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_nextline(shell_info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			shell_info->linecount_flag = 1;
			comment_remover(*buf);
			addcmd_history(shell_info, *buf, shell_info->histcount++);
			{
				*len = r;
				shell_info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * line_nonline - gets a line minus the newline
 * @shell_info: pointer to a structure
 *
 * Return: number of bytes read
 */

ssize_t line_nonline(info_t *shell_info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(shell_info->arg), *p;

	str_printsingle(BUF_FLUSH);
	r = buf_chcommands(shell_info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		chain_checker(shell_info, buf, &j, i, len);
		while (j < len)
		{
			if (isbufchar_chain(shell_info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			shell_info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (str_len(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * buf_reader - reads a buffer
 *
 * @shell_info: pointer to a structure
 * @buf: a buffer
 * @i: address of a variable of the size of the buffer
 *
 * Return: r
 */

ssize_t buf_reader(info_t *shell_info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(shell_info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_nextline - reads the next line of input from STDIN
 *
 * @shell_info: pointer to a structure
 * @ptr: address of pointer to buffer
 * @length: address of a variable of the size of buffer
 *
 * Return: s
 */

int get_nextline(info_t *shell_info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = buf_reader(shell_info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = str_findchar(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = blockmem_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		str_nconcat(new_p, buf + i, k - i);
	else
		str_ncopy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


/**
 * ctrlc_blocker - blocks Ctrl-C
 * @sig_num: integer of the signal number
 *
 * Return: void
 */

void ctrlc_blocker(__attribute__((unused))int sig_num)
{
	str_print("\n");
	str_print("$ ");
	str_printsingle(BUF_FLUSH);
}
