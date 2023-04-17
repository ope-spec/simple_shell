#include <stdio.h>

/**
 * Prints all the arguments passed to the program.
 * The first argument (program name) is skipped.
 *
 * @param argc Number of arguments
 * @param argv Array of argument strings
 * @return 0 on success
 */
int main(int argc, char **argv)
{
    char **p = argv;

    /* Skip the first argument (program name) */
    p++;

    /* Print the remaining arguments */
    while (*p != NULL) {
        printf("%s\n", *p);
        p++;
    }

    return 0;
}
