#include "shell.h"

int stringLen(const char *s);
char *copy_string(char *ourDesti, const char *oursource);
char *string_concat(char *ourDesti, const char *oursource);
char *str_n_concat(char *ourDesti, const char *oursource, size_t n);

/**
 * stringLen - this function is a copy of strlen.
 * @s: str pointer.
 * Return: lenght of str.
 * amine mohamed and boukhriss
 */
int stringLen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

/**
 * copy_string - this function is a copy of strcp fun.
 * @ourDesti: ourDesti ppointeer str.
 * @oursource: str ponter.
 * Return: Pointer to ourDesti.
 */
char *copy_string(char *ourDesti, const char *oursource)
{
	size_t i;

	for (i = 0; oursource[i] != '\0'; i++)
		ourDesti[i] = oursource[i];
	ourDesti[i] = '\0';
	return (ourDesti);
}

/**
 * string_concat - this function is a copy of strcat fun.
 * @ourDesti: ourDesti ppointeer str.
 * @oursource: str ponter.
 * Return: return char.
 */
char *string_concat(char *ourDesti, const char *oursource)
{
	char *ourDestiTemp;
	const char *oursourceTemp;

	ourDestiTemp = ourDesti;
	oursourceTemp =  oursource;

	while (*ourDestiTemp != '\0')
		ourDestiTemp++;

	while (*oursourceTemp != '\0')
		*ourDestiTemp++ = *oursourceTemp++;
	*ourDestiTemp = '\0';
	return (ourDesti);
}

/**
 * str_n_concat - this function is a copy of strncat fun.
 * @ourDesti: ourDesti ppointeer str.
 * @oursource: str ponter.
 * @n: number of bytes.
 * Return: return char.
 */
char *str_n_concat(char *ourDesti, const char *oursource, size_t n)
{
	size_t ourDesti_len = stringLen(ourDesti);
	size_t i;

	for (i = 0; i < n && oursource[i] != '\0'; i++)
		ourDesti[ourDesti_len + i] = oursource[i];
	ourDesti[ourDesti_len + i] = '\0';

	return (ourDesti);
}
