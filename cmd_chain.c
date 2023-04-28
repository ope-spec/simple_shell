#include "shell.h"

/**
 * is_chain - tests if the current character in the buffer
 * is a command chain delimiter
 * @inf: the parameter struct
 * @buffer: the charcter buffer.
 * @pos: address of current position in buf
 *
 * Return: 1 if the character is a command chain delimiter,
 * 0 otherwise
 */
int is_chain(info_t *inf, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

/**
 * check_chain - checks if command chaining should
 * continue based on the last status
 * @inf: the parameter struct
 * @buffer: pointer to the character buffer
 * @pos: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *buffer, size_t *pos, size_t i, size_t len)
{
	size_t j = *pos;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}

	*pos = j;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * with its corresponding value
 * @inf: pointer to the parameter struct
 * Return: 1 if replacement is successful, 0 otherwise
 */
int replace_alias(info_t *inf)
{
	int i;
	list_t *node;
	char *pos;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		pos = _strchr(node->str, '=');
		if (!pos)
			return (0);
		pos = _strdup(pos + 1);
		if (!pos)
			return (0);
		inf->argv[0] = pos;
	}
	return (1);
}

/**
 * replace_vars - replaces environment variables in the tokenized string
 * @inf: pointer to the parameter struct
 * Return: 1 if replacement is successful, 0 otherwise
 */
int replace_vars(info_t *inf)
{
	int i = 0;
	list_t *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_strcmp(inf->argv[i], "$?"))
		{
			replace_string(&(inf->argv[i]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			replace_string(&(inf->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces the contents of an old string
 * with a current string
 * @prev: address of pointer to the prev string
 * @current: pointer to the new string
 *
 * Return: 1 if replacement is successful, 0 otherwise
 */
int replace_string(char **prev, char *current)
{
	free(*prev);
	*prev = current;
	return (1);
}
