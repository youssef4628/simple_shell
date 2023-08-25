#include "shell.h"

/**
 * exitProgram - exit form shell
 * @info: Structure containing potential arguments.
 *  Return: a given exit status
 */
int exitProgram(inf_t *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_check = _erroratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			error_print(info, "Illegal number: ");
			_inputs(info->argv[1]);
			_stdputchar('\n');
			return (1);
		}
		info->err_num = _erroratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _help - calles the funciton help
 * @info: Structure with potential arguments.
 *  Return: 0
 */
int _help(inf_t *info)
{
	char **argarray;

	argarray = info->argv;
	_strout("help call works. Function not yet implemented \n");
	if (0)
		_strout(*argarray);
	return (0);
}

/**
 * _mcd - changes directory
 * @info: Structure with potential arguments.
 *  Return: 0
 */
int _mcd(inf_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_r;

	s = getcwd(buffer, 1024);
	if (!s)
		_strout("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _get_env(info, "HOME=");
		if (!dir)
			chdir((dir = _get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_r = chdir(dir);
	}
	else if (str_comparison(info->argv[1], "-") == 0)
	{
		if (!_get_env(info, "OLDPWD="))
		{
			_strout(s);
			_putchar('\n');
			return (1);
		}
		_strout(_get_env(info, "OLDPWD=")), _putchar('\n');
			chdir((dir = _get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_r = chdir(info->argv[1]);
	if (chdir_r == -1)
	{
		error_print(info, "can't cd to ");
		_inputs(info->argv[1]), _stdputchar('\n');
	}
	else
	{
		_set_enviro(info, "OLDPWD", _get_env(info, "PWD="));
		_set_enviro(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
