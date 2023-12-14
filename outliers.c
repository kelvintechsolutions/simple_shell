#include "shell.h"

/**
 *_eputs - the function outputs an input string
 * @str: string.
 */

void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - function writes the character c to standard eror
 * @c: character input
 * Return: 1 if success and -1 if unsuccesful
 */

int _eputchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 * _putfd - function writes character c to given fole descriptro
 * @c: input character
 * @fd: filedescriptor
 * Return: 1
 */

int _putfd(char c, int fd)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 *_putsfd -function outputs an input string
 * @str: input string
 * @fd: filedescriptor
 * Return: number of chars
 */

int _putsfd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += _putfd(*str++, fd);
	}
	return (index);
}
