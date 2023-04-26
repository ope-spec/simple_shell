#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			handle_file_error(argv[0], argv[1]);
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}

/**
 * handle_file_error - handles file errors
 * @executable_filename: name of the executable file
 * @error_filename: name of the file that caused the error
 */
void handle_file_error(char *executable_filename, char *error_filename)
{
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
	{
		_eputs(executable_name);
		_eputs(": 0: Can't open ");
		_eputs(filename);
		_eputchar('\n');
		_eputchar(BUF_FLUSH);
		exit(127);
	}
}
