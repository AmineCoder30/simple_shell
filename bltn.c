#include "shell.h"

int set_shellVar(char **amgt, char __attribute__((__unused__)) **ourfront);
void set_alias(char *var_name, char *value);
void print_alias(alstype *alias);

/**
 * set_shellVar - this function allow to prints all aliases
 * @amgt: array of amgt.
 * @ourfront: double pointer.
 * Return: return -1 or 0.
 * amine mohamed
 */
int set_shellVar(char **amgt, char __attribute__((__unused__)) **ourfront)
{
	alstype *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!amgt[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; amgt[i]; i++)
	{
		temp = aliases;
		value = char_string(amgt[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (compare_string(amgt[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = func_createErr(amgt + i, 1);
		}
		else
			set_alias(amgt[i], value);
	}
	return (ret);
}

/**
 * set_alias - this functon set alias needed
 * @var_name: the name of needed alias.
 * @value: this var is the Value of the alias.
 * amine mohamed
 */
void set_alias(char *var_name, char *value)
{
	alstype *temp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = stringLen(value) - copy_of_spn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (compare_string(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - this function to  Prints alias.
 * @alias: ptr to alias var.
 * amine mohamed
 */
void print_alias(alstype *alias)
{
	char *alias_string;
	int len = stringLen(alias->name) + stringLen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	copy_string(alias_string, alias->name);
	string_concat(alias_string, "='");
	string_concat(alias_string, alias->value);
	string_concat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * alias_replacement - replace the matching alias.
 * @amgt: ptr to arg.
 * Return: retturn the arg.
 * amine mohamed
 */
char **alias_replacement(char **amgt)
{
	alstype *temp;
	int i;
	char *new_value;

	if (compare_string(amgt[0], "alias") == 0)
		return (amgt);
	for (i = 0; amgt[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (compare_string(amgt[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (stringLen(temp->value) + 1));
				if (!new_value)
				{
					fn_to_free_arg(amgt, amgt);
					return (NULL);
				}
				copy_string(new_value, temp->value);
				free(amgt[i]);
				amgt[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (amgt);
}
