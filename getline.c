#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints "$ " and waits for user input
 *
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;

    printf("$ ");
    while (getline(&line, &len, stdin) != -1)
    {
        printf("%s", line);
        printf("$ ");
    }

    free(line);
    line = NULL;
    return (0);
}
