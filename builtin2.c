#include "shell.h"

/**
 * _myexit - exits the shell
 * @inf: Structure containing potential arguments.
 * Return: exits with a given exit status
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
 * _mycd - changes the current directory of the shell process
 * @inf: Structure containing potential arguments.
 * Return: Always 0
 */
int _mycd(info_t *inf)
{
	char *s, *dir, buffer[1024];
	int new_dir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenv(inf, "HOME=");
		if (!dir)
			new_dir = /* TODO: what should this be? */
				chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
		else
			new_dir = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		new_dir = /* TODO: what should this be? */
			chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		new_dir = chdir(inf->argv[1]);
	if (new_dir == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
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
