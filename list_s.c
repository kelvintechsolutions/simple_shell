#include "shell.h"

/**
 * add_node -the function adds a node to the start of a list
 * @head: head pointer
 * @str: string
 * @num: number
 * Return: list size.
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
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
 * add_node_end - function adds a node to the end of the list
 * @head: head pointer
 * @str: string
 * @num: number
 * Return: list size
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
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
 * print_list_str - function outputs only the string element
 * @h: first node pointer
 * Return: list size
 */

size_t print_list_str(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * delete_node_at_index - function deletes node at a given index
 * @head: head pointer
 * @index: node index
 * Return: 1 if success or 0 if unsuccessful
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int m = 0;

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
		if (m == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		m++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - function frees all nodes of a list
 * @head_ptr: pointer address
 * Return: void
 */

void free_list(list_t **head_ptr)
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
