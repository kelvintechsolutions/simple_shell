#include "shell.h"

/**
 * _myhistory - this function displays the history list
 * @info: information parameter
 *  Return: 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - this function unsets alias to string
 * @info: information parameter
 * @str: string
 * Return: 0
 */

int unset_alias(info_t *info, char *str)
{
	char *p, m;
	int retrn;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	m = *p;
	*p = 0;
	retrn = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = m;
	return (retrn);
}

/**
 * set_alias - function sets alias to string
 * @info: information parameter
 * @str: string
 * Return: 0
 */

int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - it outputss an alias string
 * @node: alias node
 * Return: 0
 */

int print_alias(list_t *node)
{
	char *m = NULL, *n = NULL;

	if (node)
	{
		m = _strchr(node->str, '=');
		for (n = node->str; n <= m; n++)
			_putchar(*n);
		_putchar('\'');
		_puts(m + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - the function mimics the alias builtin
 * @info: information parameter
 *  Return: 0
 */

int _myalias(info_t *info)
{
	int index = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		p = _strchr(info->argv[index], '=');
		if (p)
			set_alias(info, info->argv[index]);
		else
			print_alias(node_starts_with(info->alias, info->argv[index], '='));
	}

	return (0);
}
