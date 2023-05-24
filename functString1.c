#include "shell.h"

char *char_string(char *s, char c);
int copy_of_spn(char *s, char *accept);
int compare_string(char *string1, char *string2);
int ncmp_string(const char *string1, const char *string2, size_t n);

/**
 * char_string - search for char in a str.
 * @s: str to be searched.
 * @c: the char looking for.
 * Return: return pointer & NULL.
 * amine mohamed and boukhriss
 */
char *char_string(char *s, char c)
{
	int index;

	for (index = 0; s[index]; index++)
	{
		if (s[index] == c)
			return (s + index);
	}

	return (NULL);
}

/**
 * copy_of_spn - function to search string.
 * @s: str to search.
 * @accept: pref var.
 * Return: num of bytes.
 */
int copy_of_spn(char *s, char *accept)
{
	int bytes = 0;
	int index;

	while (*s)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*s == accept[index])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * compare_string - this function is a copy strcp func.
 * @string1: first str.
 * @string2: second str.
 * Return: return an integer
 */
int compare_string(char *string1, char *string2)
{
	while (*string1 && *string2 && *string1 == *string2)
	{
		string1++;
		string2++;
	}

	if (*string1 != *string2)
		return (*string1 - *string2);

	return (0);
}

/**
 * ncmp_string -  this function is a copy strncp func.
 * @string1: first str.
 * @string2: second str.
 * @n: lenght of str.
 * Return: return integer.
 */
int ncmp_string(const char *string1, const char *string2, size_t n)
{
	size_t i;

	for (i = 0; string1[i] && string2[i] && i < n; i++)
	{
		if (string1[i] > string2[i])
			return (string1[i] - string2[i]);
		else if (string1[i] < string2[i])
			return (string1[i] - string2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
