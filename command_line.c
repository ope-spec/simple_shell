#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_numb);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions
 * @file_path: Path to the supposed file
 *
 * Return: 130
 */
int cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (130);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (130);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (130);
}

/**
 * proc_file_commands - Takes a file and attempts to run the commands
 * @file_path: Path to the file
 * @exe_numb: Return value of the last executed command
 *
 * Return: If file couldn't be opened - 130
 */
int proc_file_commands(char *file_path, int *exe_numb)
{
	ssize_t file, bang, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int numb;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_numb = cant_open(file_path);
		return (*exe_numb);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		bang = read(file, buffer, 119);
		if (bang  == 0 && line_size == 0)
			return (*exe_numb);
		buffer[bang] = '\0';
		line_size += bang;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	}  while (bang);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_numb);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_numb = 4;
		free_args(args, args);
		return (*exe_numb);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			numb = call_args(args, front, exe_numb);
			args = &args[++i];
			i = 0;
		}
	}
	numb = call_args(args, front, exe_numb);

	free(front);
	return (numb);
}
