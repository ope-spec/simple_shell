#include "shell.h"

/**
 * _myenv - Prints the current environment variables to
 * standard output.
 * @inf: Pointer to a struct containing potential arguments
 * Return: Always returns 0 to indicate successful
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @inf: Pointer to a structure containing potential arguments.
 * @nm: nm of the environment variable to get the value for.
 *
 * Return: The value of the environment variable,
 * or NULL if the variable is not found.
 */
char *_getenv(info_t *inf, const char *nm)
{
	list_t *node = inf->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, nm);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 * or modify an existing one.
 * @inf: Pointer to a structure containing potential arguments.
 * Return: Returns 0 if the environment variable
 * is successfully created or modified.
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable
 * @inf: Structure containing potential arguments.
 * Return: 0 on success, -1 on failure
 */
int _myunsetenv(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (-1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates a linked list with
 * the current environment
 * @inf: Structure containing potential arguments.
 * Return: 0 on success, -1 on failure
 */
int populate_env_list(info_t *inf)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	inf->env = node;
	return (0);
}
