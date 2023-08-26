#include "string.h"

/**
 * _strlen - a function that checks the string length
 * @str: pointeer to string
 * Return: length
 */
ssize_t _strlen(const char *str)
{
	const char *ch = str;

	if (!str)
		return (-1);

	while (*ch)
		ch++;

	return (ch - str);
}

/**
  * _strchr - customised strchr function
  * @str: pointer to string
  * @chr: char
  * Return: i
  */
ssize_t _strchr(const char *str, char chr)
{
	ssize_t i = 0;

	if (!str)
		return (-1);

	for (; str[i]; i++)
	{
		if (str[i] == chr)
			return (i);
	}

	return (-1);
}

/**
 * _strcpy - customised strcpy function
 * @dest: pointer to destination
 * @src: pointer to source
 * Return: destination
 */
char *_strcpy(char *dest, const char *src)
{
	char *m = dest;

	while (*src)
		*m++ = *src++;
	*m = '\0';

	return (dest);
}

/**
 * _strdup - customised strdup function
 * @str: pointer to string
 * Return: 0
 */
char *_strdup(const char *str)
{
	char *twin;
	size_t y = 0;

	if (!str)
		return (NULL);

	while (str[y++])
		;

	twin = malloc(sizeof(char) * y);
	if (!twin)
		return (NULL);

	while (y--)
		twin[y] = str[y];

	return (twin);
}

/**
 * _strcmp - customised strcmp function
 * @s1: pointer to first string
 * @s2: pointer to second string
 * Return: 0
 */
int _strcmp(const char *s1, const char *s2)
{
	for (; *s1 && *s2; ++s1, ++s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
	}

	if (*s1)
		return (1);
	if (*s2)
		return (-1);

	return (0);
}
