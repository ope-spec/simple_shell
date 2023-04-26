#include "shell.h"

/**
 **_strncpy - function that copies a string
 *@dest: pointer to the buffer to copy the string to
 *@src: pointer to the string to be copied
 *@n: maximum number of characters to copy
 *Return: pointer to the destination string ('dest')
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = '\0';

    return (dest);
}

/**
 * *_strncat - concatenates two strings
 *@dest: pointer to the first string
 *@src: pointer to the second string
 *@n: maximum number of bytes to be 
 * used from 'src'
 *Return: pointer to the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *p = dest;

	a = 0;
	b = 0;
	while (dest[i] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (p);
}

/**
 **_strchr - finds the first occurrence of
 a character in a string
 *@s: pointer to the string to search
 *@c:  character to look for
 *Return: pointer to the first occurrence of
 * the character c in s, or
 * NULL if the character is not found
 */
char *_strchr(char *p, char c)
{
	do {
		if (*p == c)
			return (s);
	} while (*p++ != '\0');

	return (NULL);
}
