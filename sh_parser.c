#include "shell.h"

/**
 * cmd_checker - selects if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: returns 1 if true, 0 otherwise
 */
int cmd_checker(inf_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicates_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicates_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * path_finder - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: the full path of cmd if found or NULL
 */
char *path_finder(inf_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_length(cmd) > 2) && begin_with(cmd, "./"))
	{
		if (cmd_checker(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicates_chars(pathstr, curr_pos, i);
			if (!*path)
				str_chain(path, cmd);
			else
			{
				str_chain(path, "/");
				str_chain(path, cmd);
			}
			if (cmd_checker(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
