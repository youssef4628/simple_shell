#include "shell.h"

/**
 *_atoi - convert string to integer
 *@c: string to be converted
 *Return: if no numbers 0
 */

int _atoi(char *c)
{
	int n, sign = 1, flag = 0, outp;
	unsigned int result = 0;

	for (n = 0;  c[n] != '\0' && flag != 2; n++)
	{
		if (c[n] == '-')
			sign *= -1;

		if (c[n] >= '0' && c[n] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (c[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		outp = -result;
	else
		outp = result;

	return (outp);
}

/**
 * interact - if shell interact it returns true
 * @info: address of struct
 *
 * Return: if interact 1, otherwise 0
 */
int interact(inf_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 *_alpha_check - alphabetic character checker
 *@s: character to be checked
 *Return: 1 if s is alphabetic, 0 if not
 */

int _alpha_check(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * delim_check - check character is a delimeter
 * @s: the character to be checked
 * @delim: delimeter string
 * Return: true 1, false 0
 */
int delim_check(char s, char *delim)
{
	while (*delim)
		if (*delim++ == s)
			return (1);
	return (0);
}
