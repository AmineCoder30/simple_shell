#include "shell.h"

/**
 * shell_exit - Exits the shell
 * @info: Pointer to the shell information structure
 * Return: Always returns 0
 */
int shell_exit(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return 1;
		}
		info->err_num = _erratoi(info->argv[1]);
		return -2;
	}
	info->err_num = -1;
	return -2;
}

/**
 * shell_cd - Changes the current directory of the process
 * @info: Pointer to the shell information structure
 * Return: Always returns 0
 */
int shell_cd(info_t *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1]) /* If no directory argument provided */
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0) /* If argument is "-" */
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return 1;
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else /* Change to the specified directory */
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1) /* Failed to change directory */
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else /* Directory change successful */
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * shell_help - Displays help information
 * @info: Pointer to the shell information structure
 * Return: Always returns 0
 */
int shell_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented\n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return 0;
}
