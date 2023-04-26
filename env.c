#include "shell.h"

/**
 * print_environment - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int print_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Pointer to the info_t struct containing
 * potential arguments.
 * @name: The name of the environment variable.
 *
 * Return: a pointer to the value of the environment
 * variable if found, otherwise NULL.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node != NULL)
	{
		p = starts_with(node->str, name);
		if (p != NULL && *p != '\0')
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a new environment variable
 * or modify an existing one
 * @info: Structure containing potential arguments.
 *  Return: 0 on success, or 1 on failure.
 */
int _mysetenv(info_t *info)
{
    /* Check if the number of arguments is correct */
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
    /* Call _setenv to set the environment variable */
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - function to remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: 0 on success, or 1 on failure.
 */
int _myunsetenv(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		_eputs("Insuffiicient arguments.\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
		_unsetenv(info, info->argv[n]);

	return (0);
}

/**
 * populate_env_list - function to populate env linked list
 * @info: Structure containing potential arguments.
 * Return: 0 on success, or 1 on failure.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&node, environ[n], 0);
	info->env = node;
	return (0);
}
