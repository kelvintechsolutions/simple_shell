#include "shell.h"

/**
 * **strtow -function that splits a string into words.
 * @str: string input
 * @d: string delimeter
 * Return: pointer
 */

char **strtow(char *str, char *d)
{
	int a, b, c, f, wordcount = 0;
	char **p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			wordcount++;

	if (wordcount == 0)
		return (NULL);
	p = malloc((1 + wordcount) * sizeof(char *));
	if (!p)
		return (NULL);
	for (a = 0, b = 0; b < wordcount; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		p[b] = malloc((c + 1) * sizeof(char));
		if (!p[b])
		{
			for (c = 0; c < b; c++)
				free(p[c]);
			free(p);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			p[b][f] = str[a++];
		p[b][f] = 0;
	}
	p[b] = NULL;
	return (p);
}

/**
 * **strtow2 - function that splits a string into two words
 * @str: string input
 * @d: string delimeter
 * Return: pointer
 */
char **strtow2(char *str, char d)
{
	int a, b, c, f, wordcount = 0;
	char **p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			wordcount++;
	if (wordcount == 0)
		return (NULL);
	p = malloc((1 + wordcount) * sizeof(char *));
	if (!p)
		return (NULL);
	for (a = 0, b = 0; b < wordcount; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		p[b] = malloc((c + 1) * sizeof(char));
		if (!p[b])
		{
			for (c = 0; c < b; c++)
				free(p[c]);
			free(p);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			p[b][f] = str[a++];
		p[b][f] = 0;
	}
	p[b] = NULL;
	return (p);
}
