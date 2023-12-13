#include "shell.h"

/**
 * is_chain - it tests if current character in buffer is a chain delimeter
 * @info: information parameter
 * @buf: buffering parameter
 * @p: pointer address
 * Return: 1
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t m = *p;

	if (buf[m] == '|' && buf[m + 1] == '|')
	{
		buf[m] = 0;
		m++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[m] == '&' && buf[m + 1] == '&')
	{
		buf[m] = 0;
		m++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[m] == ';')
	{
		buf[m] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = m;
	return (1);
}

/**
 * check_chain - it checks if we should conitnue with chaining
 * @info: information parameter
 * @buf: the char buffer
 * @p: address of current position in buffer
 * @i: starting position
 * @len: buffer length
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t m = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[m] = 0;
			m = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}

	*p = m;
}

/**
 * replace_alias - it replaces an aliases in the tokenized string
 * @info: information parameter
 * Return: 1
 */

int replace_alias(info_t *info)
{
	int index;
	list_t *node;
	char *ptr;

	for (index = 0; index < 10; index++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - it replaces variables in the tokenized string
 * @info: information parameter
 * Return: 1
 */

int replace_vars(info_t *info)
{
	int index = 0;
	list_t *node;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!_strcmp(info->argv[index], "$?"))
		{
			replace_string(&(info->argv[index]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[index], "$$"))
		{
			replace_string(&(info->argv[index]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[index][1], '=');
		if (node)
		{
			replace_string(&(info->argv[index]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[index], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - it replaces string
 * @old: old srring adrees
 * @new: new stringaddress
 * Return: 1
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
