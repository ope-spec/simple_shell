#include "shell.h"

/**
 * add_node - Adds a new node to the beginning of a linked list
 * @a: Pointer to a pointer to the head of the linked list
 * @p: The ping value to be assigned to the new node
 * @i: The node index to be assigned to the new node
 *
 * Return: A pointer to the newly created node
 * or NULL if an error occurs
 */
list_t *add_node(list_t **a, const char *p, int i)
{
	list_t *new_head;

	if (!a)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->i = i;
	if (p)
	{
		new_head->p = _pdup(p);
		if (!new_head->p)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *a;
	*a = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @a: address of pointer to head node
 * @p: p field of node
 * @i: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **a, const char *p, int i)
{
	list_t *n, *node;

	if (!a)
		return (NULL);

	node = *a;
	n = malloc(sizeof(list_t));
	if (!n)
		return (NULL);
	_memset((void *)n, 0, sizeof(list_t));
	n->i = i;
	if (p)
	{
		n->p = _pdup(p);
		if (!n->p)
		{
			free(n);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n;
	}
	else
		*a = n;
	return (n);
}

/**
 * print_list_p - prints only the p element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_p(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->p ? h->p : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @a: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **a, unsigned int index)
{
	list_t *node, *k;
	unsigned int i = 0;

	if (!a || !*a)
		return (0);

	if (!index)
	{
		node = *a;
		*a = (*a)->next;
		free(node->p);
		free(node);
		return (1);
	}
	node = *a;
	while (node)
	{
		if (i == index)
		{
			k->next = node->next;
			free(node->p);
			free(node);
			return (1);
		}
		i++;
		k = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @b: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **b)
{
	list_t *node, *next_node, *a;

	if (!b || !*b)
		return;
	a = *b;
	node = a;
	while (node)
	{
		next_node = node->next;
		free(node->p);
		free(node);
		node = next_node;
	}
	*b = NULL;
}
