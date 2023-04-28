#include "shell.h"

/**
 * display_command_history - Displays the history list,
 * one command per line, preceded
 * with line numbers starting at 0.
 * @inf: Structure containing potential arguments.
 * Return: Always 0
 */
int display_command_history(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * unset_alias - Removes an alias for a given command string.
 * @inf: parameter struct
 * @str: The string to remove an alias for.
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *inf, char *str)
{
	char *equals_sign, old_char;
	int ret;

	equals_sign = _strchr(str, '=');
	if (!equals_sign)
		return (1);

	old_char = *equals_sign;
	*equals_sign = 0;

	ret = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, str, -1)));
	*equals_sign = old_char;

	return (ret);
}

/**
 * set_alias - Sets an alias for a given command string.
 * @inf: parameter struct
 * @str: The string to create an alias for.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *inf, char *str)
{
	char *equals_sign;

	equals_sign = _strchr(str, '=');
	if (!equals_sign)
		return (1);
	if (!*++equals_sign)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints the alias string for a given alias node.
 * @node: The alias node to print.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *equals_sign = NULL, *a = NULL;

	if (node)
	{
		equals_sign = _strchr(node->str, '=');
		for (a = node->str; a <= equals_sign; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(equals_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the functionality of the alias command.
 * Allows users to create, list, and remove aliases for commands.
 * @inf: Structure containing potential arguments.
 * Return: Always 0
 */
int _myalias(info_t *inf)
{
	int i = 0;
	char *equals_sign = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		equals_sign = _strchr(inf->argv[i], '=');
		if (equals_sign)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
