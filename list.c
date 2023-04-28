#include "shell.h"

/**
 * add_node - Adds a new node to the beginning of a linked list
 * @head: Pointer to a pointer to the head of the linked list
 * @str: The string value to be assigned to the new node
 * @num: The length of the string value to be assigned to the new node
 *
 * Return: A pointer to the newly created node, or NULL on failure
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = _strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}
/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: string field of node
 * @num: node index used by history
 *
 * Return: A pointer to the newly added node, or NULL on failure
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nd, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_nd = malloc(sizeof(list_t));
	if (!new_nd)
		return (NULL);
	_memset((void *)new_nd, 0, sizeof(list_t));
	new_nd->num = num;
	if (str)
	{
		new_nd->str = _strdup(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_nd;
	}
	else
		*head = new_nd;
	return (new_nd);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: Pointer to the head node
 * Return: Pointer to the head node
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: pointer to the address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list_t linked list
 * @ptr: Pointer to the address of the head node
 * Return: void
 */
void free_list(list_t **ptr)
{
	list_t *node, *next_node, *head;

	if (!ptr || !*ptr)
		return;
	head = *ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ptr = NULL;
}
