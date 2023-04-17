#include <stdlib.h>
#include <string.h>

/**
 * _setenv - Sets or adds the value of an environment variable
 * @name: Name of the environment variable
 * @value: Value to be set
 * @overwrite: Flag to indicate whether to overwrite the variable if it exists
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
        return (-1); // Invalid name

    size_t len = strlen(name) + strlen(value) + 2;
    char *env = malloc(len);

    if (env == NULL)
        return (-1); // Out of memory

    int result;
    snprintf(env, len, "%s=%s", name, value);

    if (overwrite || getenv(name) == NULL)
        result = putenv(env);
    else
        result = 0;

    if (result != 0)
        free(env);

    return (result);
}
