#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH 1024

/**
 * print_path_directories - Prints each directory in the PATH environment variable.
 */
void print_path_directories(void)
{
    char *path_env = getenv("PATH");
    char path[MAX_PATH];

    if (!path_env) {
        printf("PATH environment variable is not set.\n");
        return;
    }

    strcpy(path, path_env);

    char *dir = strtok(path, ":");

    while (dir != NULL) {
        printf("%s\n", dir);
        dir = strtok(NULL, ":");
    }
}

/**
 * main - Example usage of print_path_directories.
 *
 * Return: Always 0
 */
int main(void)
{
    print_path_directories();
    return 0;
}
