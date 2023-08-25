#include "shell.h"

/**
 * _put_fd - write character c to fd
 * @c: character to be printed
 * @fd: filedescriptor
 *
 * Return: 1.
 */
int _put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_puts_fd - print input
 * @str: string to be printed
 * @fd: filedescriptor
 *
 * Return: number of char
 */
int _puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _put_fd(*str++, fd);
	}
	return (i);
}

/**
 *_inputs - prints input
 * @str: string printed
 *
 * Return: void
 */
void _inputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_stdputchar(str[i]);
		i++;
	}
}

/**
 * _stdputchar - character to stderr
 * @c: character to be printed
 *
 * Return:  1.
 */
int _stdputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
