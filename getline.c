#include "shell.h"

void *fn_reset_sz(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t fn_get_ln(char **lineptr, size_t *n, FILE *stream);

/**
 * fn_reset_sz - this function change the size of ptr.
 * @ourptr: memory is pointer.
 * @sizeOld: return old size.
 * @sizeNew: return new size.
 * Return: return old or new size.
 * amine mohamed and boukhriss
 */
void *fn_reset_sz(void *ourptr, unsigned int sizeOld, unsigned int sizeNew)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (sizeNew == sizeOld)
		return (ourptr);

	if (ourptr == NULL)
	{
		mem = malloc(sizeNew);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (sizeNew == 0 && ourptr != NULL)
	{
		free(ourptr);
		return (NULL);
	}

	ptr_copy = ourptr;
	mem = malloc(sizeof(*ptr_copy) * sizeNew);
	if (mem == NULL)
	{
		free(ourptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < sizeOld && index < sizeNew; index++)
		filler[index] = *ptr_copy++;

	free(ourptr);
	return (mem);
}

/**
 * assign_lineptr - this function assign the linptr.
 * @lineptr: for storing text.
 * @n: linprt size.
 * @buffer: The text.
 * @b: buufer size.
 * amine mohamed and boukhriss.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		copy_string(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * fn_get_ln - this function read the inpt.
 * @ptrline: for storing the input.
 * @n: linepointer seze.
 * @strm: to strm the reading input.
 * Return: num of bytes.
 * amine mohamed and boukhris.
 */
ssize_t fn_get_ln(char **ptrline, size_t *n, FILE *strm)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(strm);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = fn_reset_sz(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(ptrline, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
