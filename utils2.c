#include "shell.h"

/**
 * _eputs - writes the input string to the
 * standard error stream (stderr).
 * @str: pointer to the string to be printed
 * Return: Void
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes a character to the
 * standard error stream (stderr).
 * @j: The character to print
 *
 * Return: On success, 1. On failure,
 * -1 is returned and errno is set.
 */
int _eputchar(char j)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (j == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (j != BUF_FLUSH)
		buffer[i++] = j;
	return (1);
}

/**
 * _putfd - writes a character to the given file descriptor.
 * @j: The character to print
 * @file_descriptor: The file descriptor to write to
 *
 * Return: On success, 1. On failure,
 * -1 is returned and errno is set.
 */
int _putfd(char j, int file_descriptor)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (j == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, buffer, i);
		i = 0;
	}
	if (j != BUF_FLUSH)
		buffer[i++] = j;
	return (1);
}

/**
 * _putsfd - prints the input string to the given file descriptor.
 * @str: the string to be printed
 * @file_descriptor: the file descriptor to write to
 *
 * Return: the number of chars written
 */
int _putsfd(char *str, int file_descriptor)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, file_descriptor);
	}
	return (i);
}
