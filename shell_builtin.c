#include "shell.h"

/**
 * _myexit - Exits the shell with a specified exit status
 * @info: Pointer to a structure containing potential arguments
 * Used to maintain constant function prototype.
 * Return: Exits with a given exit status:
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int check_exit_status;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		check_exit_status = _erratoi(info->argv[1]);
		if (check_exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = check_exit_status;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments used to
 * maintain constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int cd;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			cd =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			cd = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cd =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		cd = chdir(info->argv[1]);
	if (cd == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments used to
 * maintain constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **a;

	a = info->argv;
	_puts("Function not yet implemented \n");
	if (0)
		_puts(*a);
	return (0);
}
