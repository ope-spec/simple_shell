#include "shell.h"

/**
 * *_memset - Fills a block of memory with a constant byte.
 * @s: the pointer to the memory area
 * @byte: The byte to fill the block with.
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = byte;
	return (s);
}

/**
 * ffree - Frees a dynamically allocated array of strings.
 * @str_ptr: string of strings
 */
void ffree(char **str_ptr)
{
	char **a = str_ptr;

	if (!str_ptr)
		return;
	while (*str_ptr)
		free(*str_ptr++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: Pointer to the previous allocated block.
 * @prev_bytes: The previous size of the block in bytes.
 * @new_bytes: The new size of the block in bytes
 *
 * Return: Pointer to the reallocated block of memory.
 */
void *_realloc(void *ptr, unsigned int prev_bytes, unsigned int new_bytes)
{
	char *p;

	if (!ptr)
		return (malloc(new_bytes));
	if (!new_bytes)
		return (free(ptr), NULL);
	if (new_bytes == prev_bytes)
		return (ptr);

	p = malloc(new_bytes);
	if (!p)
		return (NULL);

	prev_bytes = prev_bytes < new_bytes ? prev_bytes : new_bytes;
	while (prev_bytes--)
		p[prev_bytes] = ((char *)ptr)[prev_bytes];
	free(ptr);
	return (p);
}
