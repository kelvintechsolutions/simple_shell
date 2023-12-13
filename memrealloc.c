#include "shell.h"

/**
 **_memset - it sets memory with a constant byte
 *@s: first parameter
 *@b: second parameter
 *@n: third parameter
 *Return: pointer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		s[index] = b;
	return (s);
}

/**
 * ffree - it frees a string
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - it reallocates memory
 * @ptr: pointer to previous malloc allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pointer;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pointer = malloc(new_size);
	if (!pointer)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pointer[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pointer);
}
