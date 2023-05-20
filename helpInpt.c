#include "shell.h"

char *arguments_get(char *ourline, int *exeRet);
int arguments_call(char **amgt, char **ourfront, int *exeRet);
int arg_runner(char **amgt, char **ourfront, int *exeRet);
int arg_handler(int *exeRet);
int argum_checker(char **amgt);

/**
 * arguments_get - function to get cmd.
 * @ourline: container ot store cmd.
 * @exeRet: vla of excuted cmd.
 * Return: null or pointer.
 * amine mohamed and boukhriss
 */
char *arguments_get(char *ourline, int *exeRet)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (ourline)
		free(ourline);

	read = fn_get_ln(&ourline, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (arguments_get(ourline, exeRet));
	}

	ourline[read - 1] = '\0';
	replace_var(&ourline, exeRet);
	line_handler(&ourline, read);

	return (ourline);
}

/**
 * arguments_call - prase and call operators.
 * @amgt: array of amgt.
 * @ourfront: double pointer.
 * @exeRet: val returned by parent process.
 * Return: val of excuted cmd.
 */
int arguments_call(char **amgt, char **ourfront, int *exeRet)
{
	int ret, index;

	if (!amgt[0])
		return (*exeRet);
	for (index = 0; amgt[index]; index++)
	{
		if (ncmp_string(amgt[index], "||", 2) == 0)
		{
			free(amgt[index]);
			amgt[index] = NULL;
			amgt = alias_replacement(amgt);
			ret = arg_runner(amgt, ourfront, exeRet);
			if (*exeRet != 0)
			{
				amgt = &amgt[++index];
				index = 0;
			}
			else
			{
				for (index++; amgt[index]; index++)
					free(amgt[index]);
				return (ret);
			}
		}
		else if (ncmp_string(amgt[index], "&&", 2) == 0)
		{
			free(amgt[index]);
			amgt[index] = NULL;
			amgt = alias_replacement(amgt);
			ret = arg_runner(amgt, ourfront, exeRet);
			if (*exeRet == 0)
			{
				amgt = &amgt[++index];
				index = 0;
			}
			else
			{
				for (index++; amgt[index]; index++)
					free(amgt[index]);
				return (ret);
			}
		}
	}
	amgt = alias_replacement(amgt);
	ret = arg_runner(amgt, ourfront, exeRet);
	return (ret);
}

/**
 * arg_runner - this function call excuted cmd.
 * @amgt: array of amgt.
 * @ourfront: double pointer.
 * @exeRet: val returned by parent process.
 * Return: val of excuted cmd.
 */
int arg_runner(char **amgt, char **ourfront, int *exeRet)
{
	int ret, i;
	int (*builtin)(char **amgt, char **ourfront);

	builtin = get_builtin(amgt[0]);

	if (builtin)
	{
		ret = builtin(amgt + 1, ourfront);
		if (ret != EXIT)
			*exeRet = ret;
	}
	else
	{
		*exeRet = func_exc(amgt, ourfront);
		ret = *exeRet;
	}

	hist++;

	for (i = 0; amgt[i]; i++)
		free(amgt[i]);

	return (ret);
}

/**
 * arg_handler - functio to call and run cmd.
 * @exeRet: vla pf parent process.
 * Return: return -1 or -2
 */
int arg_handler(int *exeRet)
{
	int ret = 0, index;
	char **amgt, *line = NULL, **ourfront;

	line = arguments_get(line, exeRet);
	if (!line)
		return (END_OF_FILE);

	amgt = parse_funct(line, " ");
	free(line);
	if (!amgt)
		return (ret);
	if (argum_checker(amgt) != 0)
	{
		*exeRet = 2;
		fn_to_free_arg(amgt, amgt);
		return (*exeRet);
	}
	ourfront = amgt;

	for (index = 0; amgt[index]; index++)
	{
		if (ncmp_string(amgt[index], ";", 1) == 0)
		{
			free(amgt[index]);
			amgt[index] = NULL;
			ret = arguments_call(amgt, ourfront, exeRet);
			amgt = &amgt[++index];
			index = 0;
		}
	}
	if (amgt)
		ret = arguments_call(amgt, ourfront, exeRet);

	free(ourfront);
	return (ret);
}

/**
 * argum_checker - finctiojn to check for special char.
 * @amgt: tokenized amgt and cmds.
 * Return: retutn 2 or O.
 */
int argum_checker(char **amgt)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; amgt[i]; i++)
	{
		cur = amgt[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (func_createErr(&amgt[i], 2));
			nex = amgt[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (func_createErr(&amgt[i + 1], 2));
		}
	}
	return (0);
}
