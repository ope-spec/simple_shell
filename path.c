#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command
 * @inf: the info struct
 * @path: path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise
 */
int is_cmd(info_t *inf, char *path)
{
	struct stat output;

	(void)inf;
	if (!path || stat(path, &output))
		return (0);

	if (output.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters from a string into a new buffer
 * @dir_str: the PATH string
 * @start: the starting index
 * @stop: the stopping index
 *
 * Return: pointer to a buffer containing the
 * full path of cmd if found, NULL otherwise
 */
char *dup_chars(char *dir_str, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (dir_str[i] != ':')
			buffer[k++] = dir_str[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_path - Find the full path of a command in the
 * PATH environment variable
 * @inf: the info struct
 * @dir_str: the PATH string
 * @cmd: the command to find
 *
 * Return: 1 if the file is an executable command, 0 otherwise
 */
char *find_path(info_t *inf, char *dir_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!dir_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!dir_str[i] || dir_str[i] == ':')
		{
			path = dup_chars(dir_str, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!dir_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
