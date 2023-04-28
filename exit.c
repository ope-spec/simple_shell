#include "shell.h"

/**
 * *_strncpy - copies a string
 * @dest: the destination string to copy to
 * @src: the source string to copy from
 * @num: the maximum number of characters to copy from src to dest
 *
 * Return: a pointer to the destination string dest.
 */
char *_strncpy(char *dest, char *src, int num)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_strncat - concatenates two strings
 * @dest: the destination string to be concatenated with
 * @src: the source string to concatenate to dest
 * @num: the maximum number of bytes from src to b
 * concatenated to dest
 *
 * Return: a pointer to the resulting string dest.
 */
char *_strncat(char *dest, char *src, int num)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		dest[i] = '\0';
	return (s);
}

/**
 * *_strchr - locate character in a string
 * @s: the string to be searched
 * @c: the character to be located
 *
 * Return: a pointer to the first occurrence of the
 * character c in the string s, or NULL if the character
 * is not found.
 */
char *_strchr(char *s, char k)
{
	do {
		if (*s == k)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
