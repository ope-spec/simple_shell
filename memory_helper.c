#include "shell.h"

/**
 * _memset - Fill memory with a given value
 * @p: Pointer to the memory block to be filled
 * @v: Value to be set
 * @len: Number of bytes to be set to the value
 *
 * Return: A pointer to the memory block
 */
char *_memset(char *p, char v, unsigned int len)
{
for (unsigned int i = 0; i < len; i++)
p[i] = v;

return (p);
}

/**
* ffree - Free an array of strings
* @str_arr: The array of strings to be freed
*/
void ffree(char **str_arr)
{
if (!str_arr)
return;

char **temp = str_arr;

while (*str_arr)
free(*str_arr++);

free(temp);
}

/**
 * _realloc - Reallocate a block of memory
 * @pp: Pointer to the previously allocated memory block
 * @old_sz: Size of the previously allocated memory block
 * @new_sz: Size of the new memory block
 *
 * Return: Pointer to the reallocated memory block
 */
void *_realloc(void *pp, unsigned int old_sz, unsigned int new_sz)
{
if (!pp)
return (malloc(new_sz));

if (!new_sz)
{
free(pp);
return (NULL);
}

if (new_sz == old_sz)
return (pp);

char *new_pp = malloc(new_sz);
if (!new_pp)
return (NULL);

old_sz = old_sz < new_sz ? old_sz : new_sz;

for (unsigned int i = 0; i < old_sz; i++)
new_pp[i] = ((char *)pp)[i];

free(pp);
return (new_pp);
}
