#include "string.h"

/**
 * _strnlen - function to check the len of a str
 * @str: str to be checked
 * @n:  number of chars
 * Return: returns the value of n
 */
ssize_t _strnlen(const char *str, size_t n)
{
	const char *ch = str;

	if (str == 0)
		return (-1);

	while (n && *ch)
		--n;
	ch++;

	return (ch - str);
}

/**
  * _strnchr - Entry to main program
  * @str: pointer to str
  * @chr: char
  * @n: size of string
  * Return: returns i or (-1)
  */
ssize_t _strnchr(const char *str, char chr, size_t n)
{
	ssize_t i;

	if (str == 0)
		return (-1);

	for (i = 0; n && str[i]; --n, ++i)
	{
		if (str[i] == chr)
			return (i);
	}

	return (-1);
}

/**
 * _strncpy - string  copy function
 * @dest: pointer to input
 * @src: source input
 * @n: size of str
 * Return: returns a dest
 */

char *_strncpy(char *dest, const char *src, size_t n)
{
	char *m = dest;

	for ( ; n && *src; --n)
		*m++ = *src++;
	if (n)
		*m = '\0';

	return (dest);
}
/**
 * _strndup - function dup a string
 * @str: the str value
 * @n: size of str to copy
 * Return: returns ULL
 */
char *_strndup(const char *str, size_t n)
{
	char *twin;
	size_t x = 0;

	if (str == 0)
		return (0);

	while (n && str[x])
		--n, x++;

	twin = malloc(sizeof(char) * (x + 1));
	if (twin == 0)
		return (0);

	twin[x] = '\0';

	while (x--)
		twin[x] = str[x];

	return (twin);
}

/**
 * _strncmp - string comparason function
 * @s1: first string
 * @s2: second string
 * @n: size of string
 * Return: returns (0) to indicate success
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	for (; n && *s1 && *s2; --n, ++s1, ++s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
	}

	if (n)
	{
		if (*s1)
			return (1);
		if (*s2)
			return (-1);
	}

	return (0);
}
