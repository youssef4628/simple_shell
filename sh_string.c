#include "shell.h"

/**
 * str_length - returns the length of the string
 * @s: the string whose length to check
 *
 * Return: an integer that presents the length of the string
 */
int str_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * str_comparison - performs lexicogarphic comparison of two strangs.
 * @s1: first string
 * @s2: second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2,
 *         zero if s1 == s2
 */
int str_comparison(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begin_with - checks if the needle begins with haystack
 * @haystack: the string to search
 * @needle: the substring to find
 *
 * Return: the address of next character of haystack or NULL
 */
char *begin_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * str_chain - chains two strings
 * @dest: the destination to the buffer
 * @src: the source buffer
 *
 * Return: the pointer to destination to the buffer
 */
char *str_chain(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
