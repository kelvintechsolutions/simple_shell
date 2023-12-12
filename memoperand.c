#include "shell.h"

/**
 * bfree - frees a pointer to a memory
 * @ptr: it addresses the pointer to free
 * Return: 1 if successful else 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
