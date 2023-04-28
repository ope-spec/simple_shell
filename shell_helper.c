#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @inf: the info struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @k: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char k, char *delim)
{
	while (*delim)
		if (*delim++ == k)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @k: The character to input
 * Return: 1 if k is alphabetic, 0 otherwise
 */

int _isalpha(int k)
{
	if ((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @o: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *o)
{
	int i, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (i = 0;  o[i] != '\0' && flag != 2; i++)
	{
		if (o[i] == '-')
			sign *= -1;

		if (o[i] >= '0' && o[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (o[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
