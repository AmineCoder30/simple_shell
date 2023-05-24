#include "shell.h"

char *errNum_126(char **amgt);
char *errNum_127(char **amgt);

/**
 * errNum_126 - this function to Creates an error mesg.
 * @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *errNum_126(char **amgt)
{
	char *error, *strhs;
	int len;

	strhs = _itoa(hist);
	if (!strhs)
		return (NULL);

	len = stringLen(name) + stringLen(strhs) + stringLen(amgt[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(strhs);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, strhs);
	string_concat(error, ": ");
	string_concat(error, amgt[0]);
	string_concat(error, ": Permission denied\n");

	free(strhs);
	return (error);
}

/**
 * errNum_127 - this function to Creates an error mesg.
* @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *errNum_127(char **amgt)
{
	char *error, *strhs;
	int len;

	strhs = _itoa(hist);
	if (!strhs)
		return (NULL);

	len = stringLen(name) + stringLen(strhs) + stringLen(amgt[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(strhs);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, strhs);
	string_concat(error, ": ");
	string_concat(error, amgt[0]);
	string_concat(error, ": not found\n");

	free(strhs);
	return (error);
}
