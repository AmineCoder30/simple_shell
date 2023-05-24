#include "shell.h"

int envir_shell(char **amgt, char __attribute__((__unused__)) **ourfront);
int set_envir_shell(char **amgt, char __attribute__((__unused__)) **ourfront);
int unsetEnvShell(char **amgt, char __attribute__((__unused__)) **ourfront);

/**
 * envir_shell - this function print envi used currnetly.
 * @amgt: arrray of amgt.
 * @ourfront: double ptr.
 * Return: return 0 ro 1.
 * Descr: print one arg per line
 * amine mohamed
 */
int envir_shell(char **amgt, char __attribute__((__unused__)) **ourfront)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], stringLen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)amgt;
	return (0);
}

/**
 * set_envir_shell - this function set the envir of var.
 * @amgt: array of amgt.
 * @ourfront: dounle ptr.
 * Return: return -1 or 0.
 */
int set_envir_shell(char **amgt, char __attribute__((__unused__)) **ourfront)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!amgt[0] || !amgt[1])
		return (func_createErr(amgt, -1));

	new_value = malloc(stringLen(amgt[0]) + 1 + stringLen(amgt[1]) + 1);
	if (!new_value)
		return (func_createErr(amgt, -1));
	copy_string(new_value, amgt[0]);
	string_concat(new_value, "=");
	string_concat(new_value, amgt[1]);

	env_var = fn_to_get_envir(amgt[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (func_createErr(amgt, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * unsetEnvShell - this function delete envir.
* @amgt: array of amgt.
 * @ourfront: dounle ptr.
 * Return: return -1 or 0.
 */
int unsetEnvShell(char **amgt, char __attribute__((__unused__)) **ourfront)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!amgt[0])
		return (func_createErr(amgt, -1));
	env_var = fn_to_get_envir(amgt[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (func_createErr(amgt, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
