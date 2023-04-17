#include "shell.h"


#define MAX_WORDS 100

/**
* split_string - Splits a string into an array of words
* @string: The string to be split
* @delimiter: The delimiter character
*
* Return: An array of words
*/
char **split_string(char *string, const char *delimiter)
{
    char **words = malloc(sizeof(char *) * MAX_WORDS);
    if (!words) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    int j = 0;
    int word_start = 0;

    while (string[j]) {
        if (string[j] == *delimiter) {
            // allocate space for new word
            words[i] = malloc(sizeof(char) * (j - word_start + 1));
            if (!words[i]) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }

            // copy characters of word into new space
            strncpy(words[i], &string[word_start], j - word_start);
            words[i][j - word_start] = '\0';

            // move to next word
            i++;
            word_start = j + 1;
        }
        j++;
    }

    // add last word
    words[i] = malloc(sizeof(char) * (j - word_start + 1));
    if (!words[i]) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    strncpy(words[i], &string[word_start], j - word_start);
    words[i][j - word_start] = '\0';

    // add terminating NULL pointer
    words[++i] = NULL;

    return words;
}

/**
* main - Example usage of split_string
*
* Return: Always 0
*/
int main(void)
{
    char str[] = "ls -l";
    char **args = split_string(str, " ");
    execve(args[0], args, NULL);
    perror("execve failed");
    return (EXIT_FAILURE);
}
