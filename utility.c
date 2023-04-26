#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the character to check
 * @delimeter: a string containing the delimiters to check against
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delim(char c, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@i: The character to input
 *Return: 1 if i is alphabetic, 0 otherwise
 */

int _isalpha(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@j: string to be converted
 *Return: the converted number if successful, 0 otherwise
 */

int _atoi(char *j)
{
	int i, sign = 1, flag = 0, result;
	unsigned int num = 0;

	for (i = 0;  j[i] != '\0' && flag != 2; i++)
	{
		if (j[i] == '-')
			sign *= -1;

		if (j[i] >= '0' && j[i] <= '9')
		{
			flag = 1;
			num *= 10;
			num += (j[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -num;

	return (num);
}
