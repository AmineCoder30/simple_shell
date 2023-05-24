#include "shell.h"

char *fill_path_dir(char *ourpath);
lisType *direct_path(char *ourpath);

/**
 * locate_funct - function to locate the cmd.
 * @ourcmd: set the size of cmd.
 * Return: null or path name.
 */
char *locate_funct(char *ourcmd)
{
	char **path, *temp;
	lisType *dirs, *head;
	struct stat st;

	path = fn_to_get_envir("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = direct_path(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(stringLen(dirs->dir) + stringLen(ourcmd) + 2);
		if (!temp)
			return (NULL);

		copy_string(temp, dirs->dir);
		string_concat(temp, "/");
		string_concat(temp, ourcmd);

		if (stat(temp, &st) == 0)
		{
			func_freeList(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	func_freeList(head);

	return (NULL);
}

/**
 * fill_path_dir - function to copies the path.
 * @ourpath: The path of dir.
 * Return: return str.
 */
char *fill_path_dir(char *ourpath)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(fn_to_get_envir("PWD")) + 4;
	for (i = 0; ourpath[i]; i++)
	{
		if (ourpath[i] == ':')
		{
			if (ourpath[i + 1] == ':' || i == 0 || ourpath[i + 1] == '\0')
				length += stringLen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; ourpath[i]; i++)
	{
		if (ourpath[i] == ':')
		{
			if (i == 0)
			{
				string_concat(path_copy, pwd);
				string_concat(path_copy, ":");
			}
			else if (ourpath[i + 1] == ':' || ourpath[i + 1] == '\0')
			{
				string_concat(path_copy, ":");
				string_concat(path_copy, pwd);
			}
			else
				string_concat(path_copy, ":");
		}
		else
		{
			str_n_concat(path_copy, &ourpath[i], 1);
		}
	}
	return (path_copy);
}

/**
 * direct_path - function to tokenize path of dir.
 * @ourpath: list of dir.
 * Return: a ptr with type listype.
 */
lisType *direct_path(char *ourpath)
{
	int index;
	char **dirs, *path_copy;
	lisType *head = NULL;

	path_copy = fill_path_dir(ourpath);
	if (!path_copy)
		return (NULL);
	dirs = parse_funct(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			func_freeList(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
