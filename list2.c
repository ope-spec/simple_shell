#include "shell.h"

/**
 * list_len - Determines the length of
 * a singly linked list
 * @h: Pointer to the first node of the list
 *
 * Return: The number of nodes in the linked list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h != NULL)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - converts a linked list of nodes
 * containing string data into an array of strings
 * @a: a pointer to the first node of the linked list
 *
 * Return: an array of strings representing
 * the data in the linked list
 */
char **list_to_strings(list_t *a)
{
	list_t *node = a;
	size_t i = list_len(a), j;
	char **strs;
	char *str;

	if (!a || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all the elements of
 * a linked list of type list_t
 * @h: a pointer to the first node
 * of the linked list
 *
 * Return: the size of the linked list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - searches for a node in
 * a linked list whose string starts with a
 * given prefix and the next character matches a given
 * character
 * @node: pointer to list a (head)
 * @idx: the prefix to match at the beginning of the
 * string in the node
 * @c: the character that follows the prefix in the string
 *
 * Return: a pointer to the matched node or NULL if
 * no such node is found
 */
list_t *node_starts_with(list_t *node, char *idx, char c)
{
	char *p = NULL;

	while (node != NULL)
	{
		p = starts_with(node->str, idx);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a given node
 * in a linked list
 * @a: a pointer to the first node of the linked list
 * @node: a pointer to the node whose index is to be found
 *
 * Return: the index of the node if found,
 * or -1 if the node is not in the list
 */
ssize_t get_node_index(list_t *a, list_t *node)
{
	size_t i = 0;

	while (a != NULL)
	{
		if (a == node)
			return (i);
		a = a->next;
		i++;
	}
	return (-1);
}
