#include "shell.h"

/**
 * _myhistory - displays the command history list with line numbers
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unsets an alias associated with a given string
 * @info: Structure containing potential arguments.
 * @str: the string associated with the alias to unset
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *i, j;
	int result;

	i = _strchr(str, '=');
	if (!i)
		return (1);
	j = *i;
	*i = 0;
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*i = j;
	return (result);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *i;

	i = _strchr(str, '=');
	if (!i)
		return (1);
	if (!*++i)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 1) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *i = NULL, *a = NULL;

	if (node)
	{
		i = _strchr(node->str, '=');
		for (a = node->str; a < i && *a; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(i + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
