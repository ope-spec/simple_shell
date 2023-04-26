#include "shell.h"

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: void
 */
void _eputs(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_eputchar(str[n]);
		n++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success, 1 is returned.
 * On failure, -1 is returned.
 */
int _eputchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to a given file descriptor.
 * @c: The character to print
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1 is returned.
 * On failure, -1 is returned.
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putsfd - writes the string a to a given file descriptor
 * @a: The string to be written
 * @fd: The file descriptor to write to
 *
 * Return: On success, returns the number of characters written.
 * On failure, returns -1.
 */
int _putsfd(char *a, int fd)
{
	int k = 0;

	if (!a)
		return (0);
	while (*a)
	{
		k += _putfd(*a++, fd);
	}
	return (k);
}
