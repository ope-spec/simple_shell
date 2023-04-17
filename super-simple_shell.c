#include "shell.h"

#define MAX_INPUT_SIZE 1024

/**
 * read_input - Reads a line of input from stdin
 * @input: The buffer to store the input in
 *
 * Return: The number of characters read
 */
int read_input(char *input)
{
    printf("super-simple-shell$ ");
    return fgets(input, MAX_INPUT_SIZE, stdin) ? strlen(input) : 0;
}

/**
 * parse_input - Parses a line of input into a command and its arguments
 * @input: The input to parse
 * @command: The buffer to store the command in
 *
 * Return: The number of arguments
 */
int parse_input(char *input, char *command)
{
    int i, j = 0;
    char *arg;
    int num_args = 0;

    for (i = 0; input[i]; i++) {
        if (input[i] == ' ' || input[i] == '\n') {
            if (j > 0) {
                // terminate argument with null character
                arg[j] = '\0';

                if (num_args == 0) {
                    // first argument is the command
                    strncpy(command, arg, MAX_INPUT_SIZE);
                }

                num_args++;
                j = 0;
            }
        } else {
            arg[j++] = input[i];
        }
    }

    return num_args;
}

/**
 * execute_command - Executes a command with its full path
 * @command: The command to execute
 */
void execute_command(char *command)
{
    char *argv[] = {command, NULL};

    if (execv(command, argv) == -1) {
        perror("execv failed");
        exit(EXIT_FAILURE);
    }
}

/**
 * main - Entry point of the super simple shell
 *
 * Return: Always 0
 */
int main(void)
{
    char input[MAX_INPUT_SIZE];
    char command[MAX_INPUT_SIZE];

    while (1) {
        if (read_input(input) > 0) {
            if (parse_input(input, command) > 0) {
                pid_t pid = fork();

                if (pid == -1) {
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                } else if (pid == 0) {
                    // child process
                    execute_command(command);
                } else {
                    // parent process
                    int status;
                    if (wait(&status) == -1) {
                        perror("wait failed");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }

    return 0;
}
