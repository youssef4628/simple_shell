#include "shell.h"

/**
 * _mhistory - display history
 * @info: Structure with potential arguments.
 *  Return: 0
 */
int _mhistory(inf_t *info)
{
	write_list(info->history);
	return (0);
}

/**
 * unsetAlias - sets to string
 * @info: struct
 * @str: tring alias
 *
 * Return:0 success, 1 error
 */
int unsetAlias(inf_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _stringchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_node_at_index(&(info->alias),
		obtain_node_index(info->alias, node_begins_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setalias - changes alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int setalias(inf_t *info, char *str)
{
	char *p;

	p = _stringchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (append_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printalias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printalias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _stringchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_strout(p + 1);
		_strout("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(inf_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _stringchr(info->argv[i], '=');
		if (p)
			setalias(info, info->argv[i]);
		else
			printalias(node_begins_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
