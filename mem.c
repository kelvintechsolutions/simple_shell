#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: pointer to be freed
 * Return: 1
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
