#include "shell.h"

/**
 * get_history_file - function gets the file history
 * @info: information parameter
 * Return: string
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - this function creates or appends a file
 * @info: information parameter
 * Return: 1 if success
 */

int write_history(info_t *info)
{
	ssize_t file_des;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_des = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_des == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, file_des);
		_putfd('\n', file_des);
	}
	_putfd(BUF_FLUSH, file_des);
	close(file_des);
	return (1);
}

/**
 * read_history -this function reads history from file
 * @info: information parameter
 * Return: history count
 */

int read_history(info_t *info)
{
	int index, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (index = 0; index < fsize; index++)
		if (buf[index] == '\n')
		{
			buf[index] = 0;
			build_history_list(info, buf + last, linecount++);
			last = index + 1;
		}
	if (last != index)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - this function adds entry to a history linked list
 * @info: information parameter
 * @buf: buffer
 * @linecount: count of lines
 * Return: 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history -this function renumbers the history linked list
 * @info: information parameter
 * Return: history count
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int index = 0;

	while (node)
	{
		node->num = index++;
		node = node->next;
	}
	return (info->histcount = index);
}
