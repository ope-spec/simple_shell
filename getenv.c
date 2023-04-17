#include "shell.h"

extern char **environ;

/**
 * _getenv - Retrieves the value of an environment variable
 * @name: The name of the environment variable
 *
 * Return: A pointer to the value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
    int i;
    size_t name_len;
    char *value;

    if (!name || !environ)
        return (NULL);

    name_len = strlen(name);

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(name, environ[i], name_len) == 0 && environ[i][name_len] == '=')
        {
            value = environ[i] + name_len + 1;
            return (value);
        }
    }

    return (NULL);
}
