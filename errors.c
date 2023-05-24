#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int func_createErr(char **amgt, int err);

/**
 * num_len - this function to count the length of digit.
 * @num: num of measure.
 * Return: return the lenght of digit.
 * amine mohamed and boukhriss
 */
int num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - this func convert a digit to a string.
 * @num: the number.
 * Return: return string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * func_createErr - function print a custom err.
 * @amgt: array of amgt.
 * @err: The val of error.
 * Return: return error.
 */
int func_createErr(char **amgt, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = func_envErr(amgt);
		break;
	case 1:
		error = errNum_1(amgt);
		break;
	case 2:
		if (*(amgt[0]) == 'e')
			error = exitErr_num2(++amgt);
		else if (amgt[0][0] == ';' || amgt[0][0] == '&' || amgt[0][0] == '|')
			error = syntxErr_num2(amgt);
		else
			error = changeDErr_num2(amgt);
		break;
	case 126:
		error = errNum_126(amgt);
		break;
	case 127:
		error = errNum_127(amgt);
		break;
	}
	write(STDERR_FILENO, error, stringLen(error));

	if (error)
		free(error);
	return (err);

}
