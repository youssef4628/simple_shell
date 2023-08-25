#include "shell.h"

/**
 * _set_enviro - Initialize new environment var,
 * @info: Structure with arguments.
 * @var: string env varariable property
 * @value: string env varariable value
 *  Return: 0
 */
int _set_enviro(inf_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_length(var) + str_length(value) + 2);
	if (!buf)
		return (1);
	str_cp(buf, var);
	str_chain(buf, "=");
	str_chain(buf, value);
	node = info->env;
	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	append_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * get_env - return the string array
 * @info: Structure with arguments.
 * Return: 0
 */
char **get_env(inf_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unset_enviro - Remove environment variable
 * @info: Structure with arguments.
 * @var: the string env var property
 *  Return: 1
 */
int _unset_enviro(inf_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = remove_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
