#include "shell.h"

/**
 * len_of_list - determines the length of linked list
 * @h: pointer to first node
 *
 * Return: the size of list
 */
size_t len_of_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * convert_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: the array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = len_of_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_cp(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * write_list - writes all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: the size of list
 */
size_t write_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_strout(number_convert(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_strout(h->str ? h->str : "(nil)");
		_strout("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_begins_with - returns the node whose string begins with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: the match node or null
 */
list_t *node_begins_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begin_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * obtain_node_index - obtains the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: the index of node or else -1
 */
ssize_t obtain_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
