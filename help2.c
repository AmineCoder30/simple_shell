#include "shell.h"

void line_handler(char **ourline, ssize_t read);
ssize_t get_new_len(char *ourline);
void logical_ops(char *ourline, ssize_t *newLeng);

/**
 * line_handler - this funcction parse line.
 * @ourline: line pointer.
 * @read: line len.
 */
void line_handler(char **ourline, ssize_t read)
{
	char *old_line, *new_line;
	char previous, current, next;
	size_t i, j;
	ssize_t new_len;

	new_len = get_new_len(*ourline);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *ourline;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*ourline);
	*ourline = new_line;
}

/**
 * get_new_len - this function Gets the new length of a line
 * @ourline: line will be chacked.
 * Return: The line lenght.
 */

ssize_t get_new_len(char *ourline)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; ourline[i]; i++)
	{
		current = ourline[i];
		next = ourline[i + 1];
		if (current == '#')
		{
			if (i == 0 || ourline[i - 1] == ' ')
			{
				ourline[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && ourline[i - 1] != ' ' && ourline[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (ourline[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (ourline[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&ourline[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && ourline[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - this function to  Checks a line for logical opera.
 * @ourline: char pointer.
 * @newLeng: new lenght ptr.
 */
void logical_ops(char *ourline, ssize_t *newLeng)
{
	char prev, current, next;

	prev = *(ourline - 1);
	current = *ourline;
	next = *(ourline + 1);

	if (current == '&')
	{
		if (next == '&' && prev != ' ')
			(*newLeng)++;
		else if (prev == '&' && next != ' ')
			(*newLeng)++;
	}
	else if (current == '|')
	{
		if (next == '|' && prev != ' ')
			(*newLeng)++;
		else if (prev == '|' && next != ' ')
			(*newLeng)++;
	}
}
