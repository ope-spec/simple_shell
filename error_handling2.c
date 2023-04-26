#include "shell.h"

/**
 * _erratoi - function that converts a string to an integer.
 * @i: pointer to the string to be converted.
 * Return: returns the converted integer if successful,
 * 0 if there are no numbers in the string,
 * and -1 if an error occurs.
 */
int _erratoi(char *i)
{
	int j = 0;
	unsigned long int n = 0;

	if (*i == '+')
		i++;
	for (j = 0;  i[j] != '\0'; j++)
	{
		if (i[j] >= '0' && i[j] <= '9')
		{
			n *= 10;
			n += (i[j] - '0');
			if (n > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (n);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @s: string containing specified error type
 * Return: void
 */
void print_error(info_t *info, char *s)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(s);
}

/**
 * print_d - function that prints an integer number (base 10).
 * @input: The integer to print.
 * @fd: file descriptor to write to.
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*put_char)(char) = write;
	int i, count = 0;
	unsigned int abs_input, current;

	if (fd == STDERR_FILENO)
		put_char = _eputchar;
	if (input < 0)
	{
		abs_input = -input;
		put_char('-', fd);
		count++;
	}
	else
		abs_input = input;
	current = abs_input;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_input / i)
		{
			put_char('0' + current / i, fd);
			count++;
		}
		current %= i;
	}
	put_char('0' + current, fd);
	count++;

	return (count);
}

/**
 * convert_number - Converter function that clones itoa.
 * @num: The number to convert.
 * @base: The base of the number.
 * @flags: Flags for the argument.
 *
 * Return: string containing the converted number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *a;
	static char buf[50];
	char p = 0;
	char *r;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		p = '-';

	}
	a = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	r = &buf[49];
	*r = '\0';

	do	{
		*--r = a[n % base];
		n /= base;
	} while (n != 0);

	if (p)
		*--r = p;
	return (r);
}

/**
 * remove_comments - Function that replaces
 * the first instance of '#' with '\0'.
 * @buf:  Address of the string to modify.
 *
 * Return: Always 0 (Success);
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
