#include "shell.h"

/**
 * *_strncpy - copies a string
 * @destination: the destination string to copy to
 * @src: the source string to copy from
 * @num: the maximum number of characters to copy from src to destination
 *
 * Return: a pointer to the destination string dest.
 */
char *_strncpy(char *destination, char *src, int num)
{
	int i, j;
	char *ptr = destination;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		destination[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (ptr);
}

/**
 * *_strncat - concatenates two strings
 * @destination: the destination string to be concatenated with
 * @src: the source string to concatenate to destination
 * @num: the maximum number of bytes from src to b
 * concatenated to destination
 *
 * Return: a pointer to the resulting string destination.
 */
char *_strncat(char *destination, char *src, int num)
{
	int i, j;
	char *ptr = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		destination[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		destination[i] = '\0';
	return (ptr);
}

/**
 * *_strchr - locate character in a string
 * @s: the string to be searched
 * @k: the character to be located
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
