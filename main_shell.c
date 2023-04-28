#include "shell.h"

/**
 * hsh - main shell loop.
 * @inf: pointer to the parameter and return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *inf, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(inf);
		if (r != -1)
		{
			set_info(inf, argv);
			builtin_ret = find_builtin(inf);
			if (builtin_ret == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (builtin_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command and executes it
 * @inf: pointer to the parameter and return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *inf)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", display_command_history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _cd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type != NULL; i++)
		if (_strcmp(inf->argv[0], builtintbl[i].type) == 0)
		{
			inf->line_count++;
			built_in_ret = builtintbl[i].func(inf);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Find the command in the `inf` struct and execute it if found
 *
 * @inf: Pointer to the `info_t` struct that contains the command arguments
 *
 * Return: void
 */
void find_cmd(info_t *inf)
{
	char *path = NULL;
	int i, arg_count = 0;

	inf->path = inf->argv[0];

	if (inf->linecount_flag)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0; inf->arg[i]; i++)
	{
		if (!is_delim(inf->arg[i], " \t\n"))
		{
			arg_count++;
		}
	}
	if (arg_count == 0)
	{
		return;
	}
	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path != NULL)
	{
		inf->path = path;
		fork_cmd(inf);
		return;
	}
	if (is_cmd(inf, inf->argv[0]))
	{
		fork_cmd(inf);
	}
	else if (*(inf->arg) != '\n')
	{
		inf->status = 127;
		print_error(inf, "not found\n");
	}
}


/**
 * fork_cmd - forks a new process and executes the command.
 * @inf: pointer to the info_t struct that contains the command arguments.
 *
 * Return: void.
 */
void fork_cmd(info_t *inf)
{
pid_t pid;

pid = fork();
if (pid == -1)
{
perror("fork error");
return;
}
if (pid == 0)
{
if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
{
free_info(inf, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(inf->status));
if (WIFEXITED(inf->status))
{
inf->status = WEXITSTATUS(inf->status);
if (inf->status == 126)
print_error(inf, "Permission denied\n");
}
}
}

