#include "shell.h"

/**
 * buf_input - chained commands
 * @info: parameter struct
 * @buf: buffer adress
 * @len: len var adress
 *
 * Return: bytes
 */
ssize_t buf_input(inf_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigin_handel);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			comment_remove(*buf);
			list_buildHistory(info, *buf, info->histcount++);
			/* if (_stringchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * input_get - gets a line
 * @info: parameter struct
 *
 * Return: bytes
 */
ssize_t input_get(inf_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = buf_input(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		detect_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_it_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (str_length(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * buf_read - read buffer
 * @info: parameter struct
 * @buf: buffer size
 * @i: size of buffer
 *
 * Return: returns r
 */
ssize_t buf_read(inf_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - get the next line from input STDIN
 * @info: parameter struct
 * @ptr: pointer to buffer adress
 * @length: preallocated ptr buffer size
 *
 * Return: returns (s)
 */
int _getline(inf_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = buf_read(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _stringchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = reallocates(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_stringcat(new_p, buf + i, k - i);
	else
		_stringcpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigin_handel - blocks the command ctrl-C
 * @sig_num: signal number
 *
 * Return: void always
 */
void sigin_handel(__attribute__((unused))int sig_num)
{
	_strout("\n");
	_strout("$ ");
	_putchar(BUF_FLUSH);
}
