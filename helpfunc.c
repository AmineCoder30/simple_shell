#include "shell.h"

void fn_to_free_arg(char **amgt, char **ourfront);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void replace_var(char **ourline, int *exeRet);

/**
 * fn_to_free_arg - function to free memory.
 * @amgt: double ptr contain command and amgt.
 * @ourfront: double ptr.
 */
void fn_to_free_arg(char **amgt, char **ourfront)
{
	size_t i;

	for (i = 0; amgt[i] || amgt[i + 1]; i++)
		free(amgt[i]);

	free(ourfront);
}

/**
 * get_pid - this functiojn help us to get the current pid.
 * Return: return the pid or null.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - this cunction get vla = envir value.
 * @beginning: envir to search.
 * @len: envir var lenght.
 * Return:  return an empty string or value of the envir.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	str_n_concat(var, beginning, len);

	var_addr = fn_to_get_envir(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(stringLen(temp) + 1);
		if (replacement)
			copy_string(replacement, temp);
	}

	return (replacement);
}

/**
 * replace_var - Handles variable replacement.
 * @ourline: ptr contain the envir and the amgt.
 * @exeRet: ptr to the return value .
 */
void replace_var(char **ourline, int *exeRet)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *ourline;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exeRet);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = get_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + stringLen(replacement)
					  + stringLen(&old_line[k]) + 1);
			if (!ourline)
				return;
			new_line[0] = '\0';
			str_n_concat(new_line, old_line, j);
			if (replacement)
			{
				string_concat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			string_concat(new_line, &old_line[k]);
			free(old_line);
			*ourline = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
