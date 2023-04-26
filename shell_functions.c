#include "shell.h"

/**
 * main_loop - main shell loop
 * @inf: pointer to the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_loop(info_t *inf, char **argv)
{
	ssize_t r = 0;
	int builtin_ret_val = 0;

	while (r != -1 && builtin_ret_val != -2)
	{
		clear_inf(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(inf);
		if (r != -1)
		{
			set_info(inf, argv);
			builtin_ret_val = find_builtin(inf);
			if (builtin_ret_val == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_inf(inf, 0);
	}
	write_history(inf);
	free_inf(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (builtin_ret_val == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(info->err_num);
	}
	return (builtin_ret_val);
}

/**
 * find_builtin - finds a built-in command
 * @inf: pointer to the info struct containing
 * parameter & return info
 *
 * Return: -1 if built-in not found,
 *	0 if built-in executed successfully,
 *	1 if built-in found but not successful,
 *	-2 if built-in signals exit()
 */
int find_builtin(info_t *inf)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(inf->argv[0], builtintbl[i].type) == 0)
		{
			inf->line_count++;
			built_in_ret = builtintbl[i].func(inf);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @inf: pointer to the struct containing information about command
 *
 * Return: void
 */
void find_cmd(info_t *inf)
{
	char *path = NULL;
	int i, num = 0;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0; inf->arg[i]; i++)
	{
		if (!is_delim(inf->arg[i], " \t\n"))
			num++;
	}

	if (!num)
		return;

	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=") || inf->argv[0][0] == '/')
			&& is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks and executes a command thread
 * @inf: pointer to information struct
 *
 * Return: void
 */
void fork_cmd(info_t *inf)
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
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		perror("Error:");
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
