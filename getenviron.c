#include "shell.h"

/**
 * get_environ - initializes new environment
 * @info: first parameter
 * Return: 0 if successful.
 */

char **get_environ(info_t *info)
{
	char **result;

	if (!info->environ || info->env_changed)
	{
		result = list_to_strings(info->env);
		info->env_changed = 0;
		info->environ = result;
	}
	return info->environ;
}

/**
 * _unsetenv - function to perform removal from environment
 * @info: Structure containing potential arguments
 *  Return: 1
 * @var: variable property
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - sets a new environment variable
 * @info: Parameter used to maintain constant function prototype.
 * @var: variable
 * @value: variable value
 *  Return: 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
