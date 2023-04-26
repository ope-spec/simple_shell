#include "shell.h"

/**
 * get_history_file - constructs the path to the history file.
 * @info: pointer to an info_t structure.
 *
 * Return: Upon successful completion, returns a
 * string containing the full path to the history file.
 * Otherwise, returns NULL.
 */

char *get_history_file(info_t *info)
{
	char *b, *d;

	d = _getenv(info, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, d);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *file = get_history_file(info);
	list_t *node = NULL;

	if (!file)
		return (-1);

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(b_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: h on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, n = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *b = NULL, *file = get_history_file(info);

	if (!file)
		return (0);

	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	b = malloc(sizeof(char) * (fsize + 1));
	if (!b)
		return (0);
	rdlen = read(fd, b, fsize);
	b[fsize] = 0;
	if (rdlen <= 0)
		return (free(b), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (b[i] == '\n')
		{
			b[i] = 0;
			build_history_list(info, b + last, n++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, b + last, n++);
	free(b);
	info->h = n;
	while (info->h-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->h);
}

/**
 * build_history_list - function to add entry to a history linked list
 * @info: structure containing potential arguments used to
 * maintain constant function prototype.
 * @b: buffer
 * @n: the history n, h
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *b, int n)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, b, n);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list
 * after alterations
 * @info: structure containing potential arguments used to
 * maintain constant function prototype.
 *
 * Return: the new history count
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->h = i);
}
