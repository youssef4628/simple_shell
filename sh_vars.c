#include "shell.h"

/**
 * is_it_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_it_chain(inf_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * detect_chain - detects that we should continue chaining based on last status
 * @info: the parameter structure
 * @buf: the character buffer
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @len: len of buffer
 *
 * Return: Void
 */
void detect_chain(inf_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}


/**
 * exchange_alias - exchanges the aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if exchanged, 0 otherwise
 */
int exchange_alias(inf_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_begins_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _stringchr(node->str, '=');
		if (!p)
			return (0);
		p = str_duplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * exchange_vars - exchanges the vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if exchanged, 0 otherwise
 */
int exchange_vars(inf_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_comparison(info->argv[i], "$?"))
		{
			exchange_string(&(info->argv[i]),
				str_duplicate(number_convert(info->status, 10, 0)));
			continue;
		}
		if (!str_comparison(info->argv[i], "$$"))
		{
			exchange_string(&(info->argv[i]),
				str_duplicate(number_convert(getpid(), 10, 0)));
			continue;
		}
		node = node_begins_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			exchange_string(&(info->argv[i]),
				str_duplicate(_stringchr(node->str, '=') + 1));
			continue;
		}
		exchange_string(&info->argv[i], str_duplicate(""));

	}
	return (0);
}

/**
 * exchange_string - exchanges the string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if exchanged, 0 otherwise
 */
int exchange_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
