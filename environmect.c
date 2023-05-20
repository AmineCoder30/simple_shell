#include "shell.h"

char **envir_fn_cp(void);
void fn_to_free_envir(void);
char **fn_to_get_envir(const char *var);

/**
 * envir_fn_cp - this function create copy of envir.
 * Return: return NULL or double pointer.
 * amine mohamed and boukhriss
 */
char **envir_fn_cp(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(stringLen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		copy_string(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * fn_to_free_envir - this function to free envir.
 * amine mohamed and boukhriss
 */
void fn_to_free_envir(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * fn_to_get_envir - this function gets envir var.
 * @var: name of envir var.
 * Return: null or double ptr.
 */
char **fn_to_get_envir(const char *var)
{
	int index, len;

	len = stringLen(var);
	for (index = 0; environ[index]; index++)
	{
		if (ncmp_string(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
