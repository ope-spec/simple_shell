#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - command that either prints all aliases
 * @args: An array of arguments
 * @front: A double pointer to the beginning of args
 *
 * Return: error occurs - -1 Otherwise - 0
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *fig = aliases;
	int i, numb = 0;
	char *value;

	if (!args[0])
	{
		while (fig)
		{
			print_alias(fig);
			fig = fig->next;
		}
		return (numb);
	}
	for (i = 0; args[i]; i++)
	{
		fig = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (fig)
			{
				if (_strcmp(args[i], fig->name) == 0)
				{
					print_alias(fig);
					break;
				}
				fig = fig->next;
			}
			if (!fig)
				numb = create_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (numb);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value
 * @var_name: Name of the alias
 * @value: Value of the alias. First character is a '='
 */
void set_alias(char *var_name, char *value)
{
	alias_t *fig = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (fig)
	{
		if (_strcmp(var_name, fig->name) == 0)
		{
			free(fig->value);
			fig->value = new_value;
			break;
		}
		fig = fig->next;
	}
	if (!fig)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - Prints the alias in the format name='value
 * @alias: Pointer to an alias
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value
 * @args: 2D pointer to the arguments
 *
 * Return: 2D pointer to the arguments
 */
char **replace_aliases(char **args)
{
	alias_t *fig;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);

	for (i = 0; args[i]; i++)
	{
		fig = aliases;
		while (fig)
		{
			if (_strcmp(args[i], fig->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(fig->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, fig->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
		}
	}
	return (args);
}
