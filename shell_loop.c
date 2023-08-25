#include "shell.h"

/**
 * hshell - main shell loop
 * @info: parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: 0 if success, 1 if error, or error code
 */
int hshell(inf_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_clear(info);
		if (interact(info))
			_strout("$ ");
		_stdputchar(BUF_FLUSH);
		r = input_get(info);
		if (r != -1)
		{
			info_set(info, av);
			builtin_ret = builtin_finder(info);
			if (builtin_ret == -1)
				cmd_finder(info);
		}
		else if (interact(info))
			_putchar('\n');
		info_free(info, 0);
	}
	history_write(info);
	info_free(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * builtin_finder - finds a builtin commands
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 elif builtin executed successfully,
 *			1 elif builtin found but not executed successfully,
 *			-2 if builtin signals exit()
 */
int builtin_finder(inf_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exitProgram},
		{"env", _my_env},
		{"help", _help},
		{"history", _mhistory},
		{"setenv", _my_set_env},
		{"unsetenv", _my_unset_env},
		{"cd", _mcd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_comparison(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * cmd_finder - finds a command in PATH
 * @info: parameter & return info struct
 *
 * Return: void
 */
void cmd_finder(inf_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!delim_check(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = path_finder(info, _get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_the_cmd(info);
	}
	else
	{
		if ((interact(info) || _get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && cmd_checker(info, info->argv[0]))
			fork_the_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			error_print(info, "not found\n");
		}
	}
}

/**
 * fork_the_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_the_cmd(inf_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			info_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				error_print(info, "Permission denied\n");
		}
	}
}
