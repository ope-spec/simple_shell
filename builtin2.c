#include "shell.h"

/**
 * _myexit - Exits the shell
 * @inf: Structure containing potential arguments
 *
 * Return: Exits with a given exit status
 */
int _myexit(info_t *inf)
{
	int check_exit;

	if (inf->argv[1])
	{
		check_exit = _erratoi(inf->argv[1]);
		if (check_exit == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}


/**
 * _cd - changes the current directory of the shell process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _cd(info_t *info)
{
	char *cwd, buffer[1024];
	int new_dir;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		new_dir = _cd_home(info);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		new_dir = _cd_prev(info, cwd);
	}
	else
	{
		new_dir = chdir(info->argv[1]);
	}

	if (new_dir == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_putchar('\n');
	}
	else
	{
		_setenv(info, "prev_pwd", _getenv(info, "curr_pwd="));
		_setenv(info, "curr_pwd", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _cd_home - handles 'cd' without arguments
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error
 */
int _cd_home(info_t *info)
{
	char *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
	{
		return (chdir((dir = _getenv(info, "curr_pwd=")) ? dir : "/"));
	}
	else
	{
		return (chdir(dir));
	}
}

/**
 * _cd_prev - handles 'cd -' command
 * @info: Structure containing potential arguments.
 * @cwd: The current working directory.
 * Return: 0 on success, 1 on error
 */
int _cd_prev(info_t *info, char *cwd)
{
	char *dir;

	if (!_getenv(info, "prev_pwd="))
	{
		_puts(cwd);
		_putchar('\n');
		return (1);
	}
	_puts(_getenv(info, "prev_pwd="));
	_putchar('\n');
	dir = _getenv(info, "prev_pwd=");
	return (chdir(dir ? dir : "/"));
}


/**
 * _myhelp - displays information about built-in shell commands
 * @inf: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhelp(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
