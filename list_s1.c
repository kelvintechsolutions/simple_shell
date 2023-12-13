#include "shell.h"

/**
 * list_len - function determines length of linked list
 * @h: pointer
 * Return: list size
 */

size_t list_len(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * list_to_strings - function outputs an array of strings
 * @head: pointer
 * Return: string array
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - the function prints all elements of a list_t linked list
 * @h: pointer
 * Return: list size
 */

size_t print_list(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * node_starts_with -this function returns a unique node
 * @node: pointer
 * @prefix: string
 * @c: character variabke
 * Return: node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - function gets the index of a node
 * @head: pointer to the head
 * @node: pointer to the node
 * Return: node index or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
