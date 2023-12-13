#include "shell.h"

/**
 * _strlen -it returns the length of a string
 * @s: string
 * Return: length
 */

int _strlen(char *s)
{
	int index = 0;

	if (!s)
		return (0);

	while (*s++)
		index++;
	return (index);
}

/**
 * _strcmp - it comparestwo strings lexicographically
 * @s1: first string parameter
 * @s2: second string parameter
 * Return: -1 if s1 < s2, +1 if s1 > s2, 0 if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with -function that checks if needle starts with haystack
 * @haystack: string
 * @needle: string to find
 * Return: pointer address
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - the function concatenates two strings
 * @dest: destination
 * @src: source
 * Return: pointer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
