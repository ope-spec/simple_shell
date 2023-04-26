#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: Pointer to the info struct
 * @path: Path to the file to check
 *
 * Return: 1 if the file is an executable command,
 * 0 otherwise
 */
int is_cmd(info_t *info, const char *path)
{
	struct stat st;

	if (!path || stat(path, &st) == -1)
		return (0);

	return ((st.st_mode & S_IFMT) == S_IFREG);
}

/**
 * dup_chars - Duplicates characters in a string from
 * a start index to a stop index
 * @pathstr: The string to duplicate from
 * @start: The starting index
 * @stop: The stopping index
 *
 * Return: A pointer to a new buffer with the
 * duplicated characters
 */
char *dup_chars(const char *pathstr, int start, int stop)
{
	char *buf = malloc(stop - start + 1);

	if (!buf)
		return (NULL);

	int k = 0;

	for (int i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = '\0';

	return (buf);
}

/**
 * find_path - Finds the full path to a command
 * in the PATH environment variable
 * @info: Pointer to the info struct
 * @pathstr: The value of the PATH environment variable
 * @cmd: The command to find
 *
 * Return: A pointer to a string with the full
 * path to the command if found, or NULL if not found
 */
char *find_path(info_t *info, const char *pathstr, const char *cmd)
{
	if (!pathstr)
		return (NULL);

	if (cmd[0] == '/')
		return (is_cmd(info, cmd) ? strdup(cmd) : NULL);

	if (strncmp(cmd, "./", 2) == 0)
		return (is_cmd(info, cmd) ? strdup(cmd) : NULL);

	char *path = strdup(pathstr);
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char *full_path = calloc(strlen(token) + strlen(cmd) + 2, sizeof(char));

		if (!full_path)
		{
			free(path);
			return (NULL);
		}

		strcat(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (is_cmd(info, full_path))
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}
