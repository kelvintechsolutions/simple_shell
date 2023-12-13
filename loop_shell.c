#include "shell.h"

/**
 * hsh - it loops over the shell
 * @info: information parameter
 * @av: argument vector
 * Return: 0 if successful.
 */

int hsh(info_t *info, char **av)
{
	ssize_t m = 0;
	int builtin_return = 0;

	while (m != -1 && builtin_return != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		m = get_input(info);
		if (m != -1)
		{
			set_info(info, av);
			builtin_return = find_builtin(info);
			if (builtin_return == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_return);
}

/**
 * find_builtin - It locates a builtin command
 * @info: information parameter
 * Return: 0 if successful
 */

int find_builtin(info_t *info)
{
	int index, built_in_return = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
		if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			built_in_return = builtintbl[index].func(info);
			break;
		}
	return (built_in_return);
}

/**
 * find_cmd - it locates command in PATH
 * @info: information parameter
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int index, val_p;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (index = 0, val_p = 0; info->arg[index]; index++)
		if (!is_delim(info->arg[index], " \t\n"))
			val_p++;
	if (!val_p)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - it forks an executable thread to run command
 * @info: information parameter
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
