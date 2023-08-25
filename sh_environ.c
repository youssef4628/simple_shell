#include "shell.h"

/**
 * Popenvlist - env linked list
 * @info: Structure with arguments.
 * Return: 0
 */
int Popenvlist(inf_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * _my_env - print current environment
 * @info: Structure with  arguments.
 * Return: 0
 */
int _my_env(inf_t *info)
{
	write_list_str(info->env);
	return (0);
}

/**
 * _get_env - get value of environment
 * @info: Structure with argunemt
 * @name: env var name
 *
 * Return: value
 */
char *_get_env(inf_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begin_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _my_unset_env - Remove environment
 * @info: Structure with arguments.
 *  Return: 0
 */
int _my_unset_env(inf_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_inputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unset_enviro(info, info->argv[i]);

	return (0);
}

/**
 * _my_set_env - Initialize new environment
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0
 */
int _my_set_env(inf_t *info)
{
	if (info->argc != 3)
	{
		_inputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_enviro(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
