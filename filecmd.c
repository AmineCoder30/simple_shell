#include "shell.h"

int cant_open(char *file_path);
int prFileCmd(char *file_path, int *exeRet);

/**
 * cant_open - print can not open error.
 * @file_path: the path of file.
 * Return: num 127.
 * amine mohamed and boukhriss
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = stringLen(name) + stringLen(hist_str) + stringLen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": Can't open ");
	string_concat(error, file_path);
	string_concat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * prFileCmd - this function run the cmd stored
 * @file_path: the path of file.
 * @exeRet:the value of excuted comd.
 * Return: return 127 or -1.
 */
int prFileCmd(char *file_path, int *exeRet)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **amgt, **ourfront;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exeRet = cant_open(file_path);
		return (*exeRet);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exeRet);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = fn_reset_sz(line, old_size, line_size);
		string_concat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	replace_var(&line, exeRet);
	line_handler(&line, line_size);
	amgt = parse_funct(line, " ");
	free(line);
	if (!amgt)
		return (0);
	if (argum_checker(amgt) != 0)
	{
		*exeRet = 2;
		fn_to_free_arg(amgt, amgt);
		return (*exeRet);
	}
	ourfront = amgt;

	for (i = 0; amgt[i]; i++)
	{
		if (ncmp_string(amgt[i], ";", 1) == 0)
		{
			free(amgt[i]);
			amgt[i] = NULL;
			ret = arguments_call(amgt, ourfront, exeRet);
			amgt = &amgt[++i];
			i = 0;
		}
	}

	ret = arguments_call(amgt, ourfront, exeRet);

	free(ourfront);
	return (ret);
}
