#include <stdlib.h>
#include <string.h>

/**
 * _unsetenv - removes a variable from the environment
 * @name: name of the variable to remove
 *
 * Return: 0 on success, -1 on error
 */
int _unsetenv(const char *name)
{
	int i, j, found = 0, len;
	char **new_env, **env;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
		return (-1); /* invalid name */

	for (len = 0; environ[len]; len++)
		;

	new_env = malloc(sizeof(char *) * len);
	if (new_env == NULL)
		return (-1); /* out of memory */

	for (i = 0, j = 0; environ[i]; i++)
	{
		if (strncmp(name, environ[i], strlen(name)) == 0 &&
		    environ[i][strlen(name)] == '=')
		{
			found = 1;
			continue;
		}
		new_env[j++] = environ[i];
	}

	if (!found)
	{
		free(new_env);
		return (0); /* not found, nothing to do */
	}

	new_env[j] = NULL;
	env = environ;
	environ = new_env;
	free(env);

	return (0);
}
