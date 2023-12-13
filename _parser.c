#include "shell.h"

/**
 * is_cmd - it investigates if a file is an executable command
 * @info: information parameter
 * @path: file path
 * Return: 1
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - the function duplicates caharacters
 * @pathstr: string path
 * @start: starting index parameter
 * @stop: stopping index parameter
 * Return: a pointer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int index = 0, val_k = 0;

	for (val_k = 0, index = start; index < stop; index++)
		if (pathstr[i] != ':')
			buf[val_k++] = pathstr[index];
	buf[val_k] = 0;
	return (buf);
}

/**
 * find_path - it locates string path
 * @info: information parameter
 * @pathstr: string path
 * @cmd: command
 * Return: path to the cmd
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int index = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[index] || pathstr[index] == ':')
		{
			path = dup_chars(pathstr, curr_pos, index);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[index])
				break;
			curr_pos = index;
		}
		index++;
	}
	return (NULL);
}
