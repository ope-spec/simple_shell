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
 * @split_char: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char k, char *split_char)
{
	while (*split_char)
		if (*split_char++ == k)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @input_str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *input_str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (i = 0;  input_str[i] != '\0' && flag != 2; i++)
	{
		if (input_str[i] == '-')
			sign *= -1;

		if (input_str[i] >= '0' && input_str[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (input_str[i] - '0');
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
