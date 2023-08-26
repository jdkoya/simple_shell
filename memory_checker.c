#include "string.h"

/**
 * _memset - Entry to main function
 * @dest: input pointer arg
 * @chr: input command
 * @n: input command size
 * Return: returns a pointer dest
 */

void *_memset(void *dest, unsigned char chr, size_t n)
{
	unsigned char *mem = dest;

	if (dest)
	{
		while (n--)
			*mem++ = chr;
	}
	return (dest);
}

/**
 * _memcpy - function that duplicates memory
 * @dest: pointer to destination
 * @src: pointer to source
 * @n: input data size
 *
 * Return: returns pointer dest
*/

void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *mem = dest;
	const unsigned char *area = src;

	if (dest && src)
	{
		while (n--)
			*mem++ = *area++;
	}
	return (dest);
}

/**
 * _memdup - copies the memory
 * @src: source pointer
 * @n: the size of memory data
 * Return: returns Null or copies the memory
 */

void *_memdup(const void *src, size_t n)
{
	void *dobs = malloc(n);
	unsigned char *mem = dobs;
	const unsigned char *area = src;

	if (dobs)
	{
		while (n--)
			*mem++ = *area++;
	}
	return (dobs);
}

/**
 * _memchr - Entry to main function
 * @src: pointer to memory source
 * @chr: character value
 * @n: input char size
 * Return: returns (-1)
 */

ssize_t _memchr(const void *src, unsigned char chr, size_t n)
{
	const unsigned char *x = src;
	ssize_t y = 0;

	if (src)
	{
		while (n--)
		{
			if (x[y] == chr)
				return (y);
			y += 1;
		}
	}
	return (-1);
}
