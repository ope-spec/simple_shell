#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
    printf("Parent process ID: %d\n", getppid());
    return (0);
}
