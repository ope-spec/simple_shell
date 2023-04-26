#include "shell.h"

/**
 * get_environ - Returns a copy of the environment
 * variables as a string array
 * @info: Structure containing relevant information
 * Return: A copy of the environment variables as a string array
 */
char **get_environ(info_t *info)
{
	if (!info->envp || info->env_changed)
	{
		info->envp = list_to_strings(info->env_lst);
		info->env_changed = 0;
	}

	return (info->envp);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing relevant information
 * @var: The name of the environment variable to be removed
 * Return: 1 if the variable was removed, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env_lst;
	size_t index = 0;
	char *prefix;

	if (!node || !var)
		return (0);

	while (node)
	{
		prefix = starts_with(node->str, var);
		if (prefix && *prefix == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env_lst), index);
			index = 0;
			node = info->env_lst;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * @info: Structure containing relevant information
 * @var: The name of the environment variable
 * @value: The value of the environment variable
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *prefix;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env_lst;
	while (node)
	{
		prefix = starts_with(node->str, var);
		if (prefix && *prefix == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env_lst), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
