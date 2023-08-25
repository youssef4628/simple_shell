#include "shell.h"

/**
 **_stringcpy - copie string
 *@dest: string to be copied to
 *@src: source string
 *@n: amount of characters
 *Return: concatenated string
 */
char *_stringcpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_stringchr - locate a character
 *@s: string to be parsed
 *@c: character to look for
 *Return: (s) a pointer
 */
char *_stringchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 **_stringcat - concatenate strings
 *@dest: first string
 *@src: second string
 *@n: the amount of bytes to be used
 *Return: concatenated string
 */
char *_stringcat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
