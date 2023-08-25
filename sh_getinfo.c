#include "shell.h"

/**
 * info_free - frees inf_t
 * @info: struct address
 * @all: true if freeing
 */
void info_free(inf_t *info, int all)
{
	f_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_li(&(info->env));
		if (info->history)
			free_li(&(info->history));
		if (info->alias)
			free_li(&(info->alias));
		f_free(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * info_clear - initializes inf_t
 * @info: struct
 */
void info_clear(inf_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info_set - initialize inf_t
 * @info: address
 * @av: argument
 */
void info_set(inf_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_to_words(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		exchange_alias(info);
		exchange_vars(info);
	}
}
