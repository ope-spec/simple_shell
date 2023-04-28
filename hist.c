#include "shell.h"

/**
 * get_history_file - gets the history file
 * @inf: the parameter struct containing potential arguments
 * Return: an allocated string containing the history file name.
 */

char *get_history_file(info_t *inf)
{
	char *buffer, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - writes history to a file
 * @inf: the parameter struct containing potential arguments
 * Return: 1 on success, else -1
 */
int write_history(info_t *inf)
{
	ssize_t file_descriptor;
	char *filename = get_history_file(inf);
	list_t *new_node = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return (-1);
	for (new_node = inf->history; new_node; new_node = new_node->next)
	{
		_putsfd(new_node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_history - reads history from file
 * @inf: the parameter struct
 * Return: the number of entries in the history list
 * after reading from file.
 */
int read_history(info_t *inf)
{
	int i, last = 0, linecount = 0;
	ssize_t file_descriptor, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(inf);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(file_descriptor, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(inf, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(inf, buffer + last, linecount++);
	free(buffer);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (inf->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @buffer: the buffer containing the command string
 * to add to the history list.
 * @linecount: the current line number for the command being added.
 *
 * Return: Always 0
 */
int build_history_list(info_t *inf, char *buffer, int linecount)
{
	list_t *new_node = NULL;

	if (inf->history)
		new_node = inf->history;
	add_node_end(&new_node, buffer, linecount);

	if (!inf->history)
		inf->history = new_node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments.
 * Return: the updated number of entries in the history list.
 */
int renumber_history(info_t *inf)
{
	list_t *new_node = inf->history;
	int i = 0;

	while (new_node)
	{
		new_node->num = i++;
		new_node = new_node->next;
	}
	return (inf->histcount = i);
}
