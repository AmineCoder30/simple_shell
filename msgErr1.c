#include "shell.h"

char *func_envErr(char **amgt);
char *errNum_1(char **amgt);
char *exitErr_num2(char **amgt);
char *changeDErr_num2(char **amgt);
char *syntxErr_num2(char **amgt);
/**
 * func_envErr - this function to Creates an error mesg.
* @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *func_envErr(char **amgt)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	amgt--;
	len = stringLen(name) + stringLen(hist_str) + stringLen(amgt[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": ");
	string_concat(error, amgt[0]);
	string_concat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * errNum_1 - this function to Creates an error mesg.
 * @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *errNum_1(char **amgt)
{
	char *error;
	int len;

	len = stringLen(name) + stringLen(amgt[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	copy_string(error, "alias: ");
	string_concat(error, amgt[0]);
	string_concat(error, " not found\n");

	return (error);
}

/**
 * exitErr_num2 - this function to Creates an error mesg.
 * @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *exitErr_num2(char **amgt)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = stringLen(name) + stringLen(hist_str) + stringLen(amgt[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": exit: Illegal number: ");
	string_concat(error, amgt[0]);
	string_concat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * changeDErr_num2 - this function to Creates an error mesg.
 * @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *changeDErr_num2(char **amgt)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (amgt[0][0] == '-')
		amgt[0][2] = '\0';
	len = stringLen(name) + stringLen(hist_str) + stringLen(amgt[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	if (amgt[0][0] == '-')
		string_concat(error, ": cd: Illegal option ");
	else
		string_concat(error, ": cd: can't cd to ");
	string_concat(error, amgt[0]);
	string_concat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * syntxErr_num2 - this function to Creates an error mesg.
* @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *syntxErr_num2(char **amgt)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = stringLen(name) + stringLen(hist_str) + stringLen(amgt[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": Syntax error: \"");
	string_concat(error, amgt[0]);
	string_concat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
