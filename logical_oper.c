#include "shell.h"

/**
 * handling_semicolon_and_operators - Handle semicolon and logical
 * @buff: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 *
 * Return: 0 on success
 */
void handling_semicolon_and_operators(char *buff, int read, char *first_av)
{
	int i;
	/*char **cmds_list = parse_user_input(buff, ";");*/
	char **cmds_list = NULL;

	execute_commands(buff, cmds_list, buff, read, first_av);
	for (i = 0; cmds_list[i] != NULL; i++)
		handling_or(cmds_list[i], read, first_av);
	free_dbl_ptr(cmds_list);
}

/**
 * handling_or - Handle || logical part
 * @buff_semicolon: first buffer that functions
 * @read: return of read
 * @first_av: av[0]
 *
 * Return: 0
 */
void handling_or(char *buff_semicolon, int read, char *first_av)
{
	int i, shape, new_shape = -3;
	char **cmds_list_1 = parse_user_input(buff_semicolon, "||");

	for (i = 0; cmds_list_1[i] != NULL; i++)
	{
		shape =  handling_and(cmds_list_1[i], read, first_av, new_shape);
		new_shape = shape
	}
	free_dbl_ptr(cmds_list_1);
}

/**
 * handling_and - Handle && logical part and executes inside of it
 * @buff_or: first buffer that functions read
 * @read: return of read
 * @new_shape: shape of ||, it is important to print
 *
 * Return: 0
 */
int handling_and(char *buff_or, int read, char *first_av, int new_shape)
{
	int s = 0, shape = 1;
	char **cmds_list_2 = parse_user_input(buff_or, "&&");

	if (new_shape == 0)
	{
		s++;
		if (cmds_list_2[s] == NULL)
			return (-1);
	}

	for (; cmds_list_2[s] != NULL; s++)
	{
		shape execute_commands(buff_or, cmds_list_2,
				cmds_list_2[s], read, first_av);
		new_shape = shape;
	}

	free_dbl_ptr(cmds_list_2);
	return (shape);
}

/**
 * execute_commands - Fork and create commands
 * @cmds_list: List of commands
 * @cmd: Single command as a string
 * @buff: first buffer
 * @read: return of read
 * @first_av: av[0]
 * Return: 0
 */
int execute_commands(char *buff, char **cmds_list,
		char *cmd, int __attribute__((unused))read, char *first_av)
{
	char **commands;
	int pid, error = 0, shape = 0, *status = process_exit_code();

	commands = parse_user_input(cmd, " ");
	handle_var_replacement(commands);
	handle_aliases(commands);

	if (handle_exit(buff, cmds_list, commands) == -1 ||
			handle_enter(commands) == 1 ||
			handle_builtins(commands) == 1)
	{
		free_dbl_ptr(commands);
		return (-1);
	}

	if (pid == 0)
	{
		error = handle_PATH(commands);
		execve(commands[0], commands);
		if (error != 0)
			handle_cmd_not_found(buff, cmds_list, commands, first_av);
		dispatch_error(first_av);
	}

	free_dbl_ptr(commands);
	return (shape);
}
