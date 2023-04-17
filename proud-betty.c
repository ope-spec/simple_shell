#include <stdio.h>

/**
 * main - Generate the Fibonacci sequence up to a user-defined limit
 * 
 * Return: Always 0 
 */
int main(void)
{
    int limit, i, j, sum;

    printf("Enter the limit for the Fibonacci sequence: ");
    scanf("%d", &limit);

    i = 0;
    j = 1;
    printf("%d %d ", i, j);

    while (i + j <= limit)
    {
        sum = i + j;
        printf("%d ", sum);
        i = j;
        j = sum;
    }

    printf("\n");

    return 0;
}
