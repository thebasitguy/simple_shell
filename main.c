#include "shell_headers.h"


/**
 * main - entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
	info_t shell_info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				custom_puts(av[0]);
				custom_puts(": 0: Can't open ");
				custom_puts(av[1]);
				buffered_putchar('\n');
				buffered_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shell_info->readfd = fd;
	}
	envlist_populate(shell_info);
	readcmd_history(shell_info);
	hsh(shell_info, av);
	return (EXIT_SUCCESS);
}

