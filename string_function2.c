#include "shell.h"

/**
 * _strlen - returns the length of a string.
 * @str: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - compares of two strangs.
 * @str1: the first string to compare
 * @str2: the second string to compare
 *
 * Return: an integer less than, equal to, or
 * greater than zero if str1 is found,
 * respectively, to be less than, to match, or be greater than str2.
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if search_str starts with input_str
 * @input_str: string to search
 * @search_str: the substring to find
 *
 * Return: address of next char of input_str or NULL
 */
char *starts_with(const char *input_str, const char *search_str)
{
	while (*search_str)
		if (*search_str++ != *input_str++)
			return (NULL);
	return ((char *)input_str);
}

/**
 * _strcat - concatenates two strings
 * @output: the destination buffer
 * @input: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *output, char *input)
{
	char *ret = output;

	while (*output)
		output++;
	while (*input)
		*output++ = *input++;
	*output = *input;
	return (ret);
}
