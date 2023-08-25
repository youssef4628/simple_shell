#include "shell.h"

/**
 * append_node - append a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: the size of list
 */
list_t *append_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_mem_setting((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = str_duplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * append_node_end - appends a node to the end of the list
 * @head: address of the pointer to the head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: the size of list
 */
list_t *append_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_mem_setting((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = str_duplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * write_list_str - writes only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: the size of list
 */
size_t write_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_strout(h->str ? h->str : "(nil)");
		_strout("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remove_node_at_index - remove node at given index
 * @head: the address of pointer to first node
 * @index: the index of node to delete
 *
 * Return: 1 if success, 0 if failure
 */
int remove_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_li - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: Void
 */
void free_li(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
