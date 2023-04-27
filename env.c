#include "shell.h"

/**
 * get_environ - Get a copy of the current environment.
 * @inf: Structure containing potential arguments.
 * Return: A pointer to a copy of the current environment
 * as an array of strings, or NULL if an error occurs.
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Unset an environment variable.
 * @inf: Structure containing potential arguments.
 * @env_var: Name of the environment variable to unset.
 * Return: 1 if the variable was unset, 0 otherwise.
 */
int _unsetenv(info_t *inf, char *env_var)
{
	list_t *node = inf->env;
	size_t i = 0;
	char *p;

	if (!node || !env_var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, env_var);
		if (p && *p == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Set the value of an environment variable.
 * @inf: Structure containing potential arguments.
 * @env_var: Name of the environment variable to set.
 * @v: Value to set the environment variable to.
 * Return: Always 0
 */
int _setenv(info_t *inf, char *env_var, char *v)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!env_var || !v)
		return (0);

	buf = malloc(_strlen(env_var) + _strlen(v) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, env_var);
	_strcat(buf, "=");
	_strcat(buf, v);
	node = inf->env;
	while (node)
	{
		p = starts_with(node->str, env_var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}
