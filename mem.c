#include "shell.h"

/**
 * free_pointer - frees a pointer and NULLs the address
 * @ptr: pointer to be freed
 * Return: 1
 */
int free_pointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
