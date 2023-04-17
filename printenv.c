#include "shell.h"

/* External variable that holds the environment */
extern char **environ;

int main(void) {
    int i = 0;

    /* Loop through the environment and print each variable */
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }

    return 0;
}
