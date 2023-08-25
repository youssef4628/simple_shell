#include "shell.h"

/**
 * getHistoryFile - gets history
 * @info: parameter
 *
 * Return: allocated string
 */

char *getHistoryFile(inf_t *info)
{
	char *buf, *dir;

	dir = _get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_length(dir) + str_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cp(buf, dir);
	str_chain(buf, "/");
	str_chain(buf, HIST_FILE);
	return (buf);
}

/**
 * history_write - creates file or append
 * @info:parameter struct
 *
 * Return: 1 on success
 */
int history_write(inf_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_puts_fd(node->str, fd);
		_put_fd('\n', fd);
	}
	_put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * historyRead - read history
 * @info: parameter
 *
 * Return: on success hiscount
 */
int historyRead(inf_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			list_buildHistory(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		list_buildHistory(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		remove_node_at_index(&(info->history), 0);
	history_renumber(info);
	return (info->histcount);
}

/**
 * list_buildHistory - add entry to a history
 * @info: Structure with arguments
 * @buf: buffer size
 * @linecount: history linecount
 *
 * Return: 0
 */
int list_buildHistory(inf_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	append_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * history_renumber - renumbers history linked list
 * @info: Structure with arguments.
 *
 * Return: histcount
 */
int history_renumber(inf_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
