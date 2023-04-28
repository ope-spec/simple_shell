#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node of the linked list.
 * Return: return the size of list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: the array of strings, or NULL if the list is empty.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **str_array;
	char *str;

	if (!head || !i)
		return (NULL);
	str_array = malloc((i + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc((_strlen(node->str) + 1) * sizeof(char));
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_array[i] = str;
	}
	str_array[i] = NULL;
	return (str_array);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to the head of the linked list
 * Return: the size of the linked list.
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
 * node_starts_with - finds a node whose string starts with prefix
 * @node: pointer to head of the list
 * @prefix: string to match
 * @o: the next character after prefix to match
 *
 * Return: pointer to the node or NULL if not found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char o)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((o == -1) || (*p == o)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head of the linked list
 * @node: pointer to the node of the linked list
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
