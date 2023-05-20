#include "shell.h"
int (*get_builtin(char *command))(char **amgt, char **ourfront);
int exit_shell(char **amgt, char **ourfront);
int change_fileDir(char **amgt, char __attribute__((__unused__)) **ourfront);
int helper_shell(char **amgt, char __attribute__((__unused__)) **ourfront);

/**
 * get_builtin - function excute cmd.
 * @command: cmd must excuted.
 * Return: return an integer.
 * amine mohamed and boukhriss
 */
int (*get_builtin(char *command))(char **amgt, char **ourfront)
{
	bltnType funcs[] = {
		{ "exit", exit_shell },
		{ "env", envir_shell },
		{ "setenv", set_envir_shell },
		{ "unsetenv", unsetEnvShell },
		{ "cd", change_fileDir },
		{ "alias", set_shellVar },
		{ "help", helper_shell },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (compare_string(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * exit_shell - function to create new process.
 * @amgt: array of amgt.
 * @ourfront: pointer.
 * Return: return -3 || 2.
 */
int exit_shell(char **amgt, char **ourfront)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (amgt[0])
	{
		if (amgt[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; amgt[0][i]; i++)
		{
			if (i <= len_of_int && amgt[0][i] >= '0' && amgt[0][i] <= '9')
				num = (num * 10) + (amgt[0][i] - '0');
			else
				return (func_createErr(--amgt, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (func_createErr(--amgt, 2));
	amgt -= 1;
	fn_to_free_arg(amgt, ourfront);
	fn_to_free_envir();
	func_free_alsList(aliases);
	exit(num);
}

/**
 * change_fileDir - function to change directory.
 * @amgt: array of amgt.
 * @ourfront: pointer.
 * Return: return 2 || -1 || 0.
 */
int change_fileDir(char **amgt, char __attribute__((__unused__)) **ourfront)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (amgt[0])
	{
		if (*(amgt[0]) == '-' || compare_string(amgt[0], "--") == 0)
		{
			if ((amgt[0][1] == '-' && amgt[0][2] == '\0') ||
					amgt[0][1] == '\0')
			{
				if (fn_to_get_envir("OLDPWD") != NULL)
					(chdir(*fn_to_get_envir("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (func_createErr(amgt, 2));
			}
		}
		else
		{
			if (stat(amgt[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(amgt[0]);
			else
			{
				free(oldpwd);
				return (func_createErr(amgt, 2));
			}
		}
	}
	else
	{
		if (fn_to_get_envir("HOME") != NULL)
			chdir(*(fn_to_get_envir("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (set_envir_shell(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (set_envir_shell(dir_info, dir_info) == -1)
		return (-1);
	if (amgt[0] && amgt[0][0] == '-' && amgt[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, stringLen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * helper_shell - function to display some info.
 * @amgt: array of amgt.
 * @ourfront: pointer.
 * Return: return -1 or - 0.
 */
int helper_shell(char **amgt, char __attribute__((__unused__)) **ourfront)
{
	if (!amgt[0])
		allHelper();
	else if (compare_string(amgt[0], "alias") == 0)
		alsHelper();
	else if (compare_string(amgt[0], "cd") == 0)
		chdirHelper();
	else if (compare_string(amgt[0], "exit") == 0)
		extHelper();
	else if (compare_string(amgt[0], "env") == 0)
		envirHelper();
	else if (compare_string(amgt[0], "setenv") == 0)
		setEnvirHelper();
	else if (compare_string(amgt[0], "unsetenv") == 0)
		unSetEnvirHelper();
	else if (compare_string(amgt[0], "help") == 0)
		hpHelper();
	else
		write(STDERR_FILENO, name, stringLen(name));

	return (0);
}
