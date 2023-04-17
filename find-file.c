#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#define PATH_MAX_LEN 4096
#define MAX_DIRS 1024

/**
 * split_string - Splits a string into an array of substrings using a delimiter
 * @string: The string to split
 * @delimiter: The delimiter character
 * @tokens: An array of char pointers to store the resulting substrings
 * @max_tokens: The maximum number of substrings to store in the tokens array
 *
 * Return: The number of substrings stored in the tokens array
 */
int split_string(char *string, char delimiter, char **tokens, int max_tokens)
{
    int num_tokens = 0;
    char *token = strtok(string, &delimiter);

    while (token != NULL && num_tokens < max_tokens) {
        tokens[num_tokens++] = token;
        token = strtok(NULL, &delimiter);
    }

    return (num_tokens);
}

/**
 * search_file - Searches for a file in a directory
 * @filename: The name of the file to search for
 * @dir: The directory to search in
 * @path: A buffer to store the resulting path of the file
 * @path_max_len: The maximum length of the path buffer
 *
 * Return: 1 if the file was found, 0 otherwise
 */
int search_file(char *filename, char *dir, char *path, size_t path_max_len)
{
    snprintf(path, path_max_len, "%s/%s", dir, filename);
    if (access(path, F_OK) == 0) {
        return (1);
    } else {
        return (0);
    }
}

/**
 * main - Entry point
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 *
 * Return: 0 on success, non-zero on error
 */
int main(int argc, char **argv)
{
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "PATH environment variable not set\n");
        return (1);
    }

    char path[PATH_MAX_LEN];
    char *dirs[MAX_DIRS];
    int num_dirs = split_string(path_env, ':', dirs, MAX_DIRS);

    int i;
    for (i = 1; i < argc; i++) {
        int j;
        int found = 0;
        for (j = 0; j < num_dirs && !found; j++) {
            if (search_file(argv[i], dirs[j], path, PATH_MAX_LEN)) {
                printf("%s\n", path);
                found = 1;
            }
        }

        if (!found) {
            fprintf(stderr, "%s: command not found\n", argv[i]);
            return (1);
        }
    }

    return (0);
}
