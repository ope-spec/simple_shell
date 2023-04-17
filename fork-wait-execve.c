#include "shell.h"

/**
 * main - Creates 5 child processes that execute the command "ls -l /tmp"
 *
 * Return: Always 0
 */
int main(void)
{
    pid_t pid;
    int status;

    // create 5 child processes
    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // child process executes ls -l /tmp
            char *args[] = {"/bin/ls", "-l", "/tmp", NULL};
            if (execve(args[0], args, NULL) == -1) {
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
        } else {
            // parent process waits for child to exit
            if (wait(&status) == -1) {
                perror("wait failed");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
