#include "string.h"

/**
 * strjoin - function to concatinate strings
 * @n: The new addr string
 * @sep: the str to be added
 * @pre: the previous string
 * @suf: the supporting str
 * Return: returns a ptr to n
 */
char *strjoin(size_t *n, const char *sep, const char *pre, const char *suf)
{
	char *dest = 0;
	size_t sep_len = _strlen(sep ? sep : "");
	size_t pre_len = _strlen(pre ? pre : "");
	size_t suf_len = _strlen(suf ? suf : "");

	dest = malloc(sizeof(char) * (pre_len + sep_len + suf_len + 1));
	if (dest)
	{
		_strcpy(dest, pre ? pre : "");
		_strcpy(dest + pre_len, sep ? sep : "");
		_strcpy(dest + pre_len + sep_len, suf ? suf : "");
		if (n)
			*n = pre_len + sep_len + suf_len + 1;
	}
	return (dest);
}


/**
 * strjoina -function to concatenate an array of strs
 * @n: Address for the new string
 * @sep: string to joined
 * @array: input array double ptr
 * Return: returns a pointer to n
 */
char *strjoina(size_t *n, const char *sep, const char **array)
{
	char *dest = 0;
	size_t len = 0, idx = 0, sep_len = _strlen(sep ? sep : "");

	while (array[idx])
		len = len + _strlen(array[idx++]);

	if (idx--)
	{
		dest = malloc(sizeof(char) * (len + idx * sep_len + 1));
		if (dest)
		{
			len = 0;
			while (*array)
			{
				_strcpy(dest + len, *array);
				len += _strlen(*array);
				if (sep_len && idx--)
				{
					_strcpy(dest + len, sep);
					len += sep_len;
				}
			}
			if (n)
				*n = len + 1;
		}
	}
	return (dest);
}


/**
 * strjoinl - function to concatenate char to strs
 * @n: size
 * @sep: ...
 * @...: variadic strs values
 * Return: a pointer
 */
char *strjoinl(size_t *n, const char *sep, ...)
{
	char *dest = 0;
	const char *temp = 0;
	size_t idx = 0, len = 0, sep_len = _strlen(sep ? sep : "");
	va_list ap;

	for (va_start(ap, sep); (temp = va_arg(ap, char *)); idx += 1)
		len += _strlen(temp);
	va_end(ap);

	if (idx--)
	{
		dest = malloc(sizeof(char) * (len + idx * sep_len + 1));
		if (dest)
		{
			len = 0;
			va_start(ap, sep);
			while ((temp = va_arg(ap, char *)))
			{
				_strcpy(dest + len, temp);
				len = len + _strlen(temp);
				if (sep_len && idx--)
				{
					_strcpy(dest + len, sep);
					len += sep_len;
				}
			}
			va_end(ap);
			if (n)
				*n = len + 1;
		}

	}
	return (dest);
}
