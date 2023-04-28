#include "shell.h"

/**
 * clear_info - Clears fields of an info_t struct
 * @inf: Pointer to the info_t struct
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info - Initializes fields of an info_t struct
 * @inf: Pointer to the info_t struct
 * @argv: Argument vector
 */
void set_info(info_t *inf, char **argv)
{
	int i = 0;

	inf->fname = argv[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(2 * sizeof(char *));
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * free_info - Frees fields of an info_t struct
 * @inf: Pointer to the info_t struct
 * @all: Flag indicating whether to free all
 * fields or just some
 */
void free_info(info_t *inf, int all)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmd_buffer)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		bfree((void **)inf->cmd_buffer);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}
