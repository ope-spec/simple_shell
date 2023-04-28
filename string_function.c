#include "shell.h"

/**
 * _strcpy - copies the string pointed to by input to
 * the buffer pointed to by output
 * @output: The buffer to which the string is to be copied
 * @input: The string to be copied
 *
 * Return: A pointer to the destination string (output)
 */
char *_strcpy(char *output, char *input)
{
	int i = 0;

	if (output == input || input == 0)
		return (output);
	while (input[i])
	{
		output[i] = input[i];
		i++;
	}
	output[i] = 0;
	return (output);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: A pointer to the duplicated string,
 * or NULL if insufficient memory
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - prints a string to standard output (stdout)
 * @str: the string to be printed
 * Return: void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to standard output (stdout)
 * @c: The character to be printed
 *
 * Return: On success, the number of characters written (1).
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
