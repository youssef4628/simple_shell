#include "shell.h"

/**
 * comment_remove - removes comment
 * @buf: address of the string
 *
 * Return: 0;
 */
void comment_remove(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * decimal_print - prints a decimal
 * @input: input
 * @fd: filedescriptor
 *
 * Return: number of characters
 */
int decimal_print(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _stdputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * number_convert - converter function
 * @num: num
 * @base: base number
 * @flags: arguments flag
 *
 * Return: number of string
 */
char *number_convert(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}


/**
 * _erroratoi - string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string
 */
int _erroratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * error_print - error message
 * @info: parameter
 * @estr: string with specified error
 * Return: 0 if no numbers in string
 */
void error_print(inf_t *info, char *estr)
{
	_inputs(info->fname);
	_inputs(": ");
	decimal_print(info->line_count, STDERR_FILENO);
	_inputs(": ");
	_inputs(info->argv[0]);
	_inputs(": ");
	_inputs(estr);
}
