#include "toks.h"

/**
 * arrjoin - a func to adds two arrays
 * @arr1: 1st array
 * @arr2: 2nd array
 *
 * Return: returns the added arrays
 */
char **arrjoin(char **arr1, char **arr2)
{
	char **length;
	size_t arr1_len = 0, arr2_len = 0;
	size_t result;

	if (arr1)
	{
		while (arr1[arr1_len])
			++arr1_len;
	}
	if (arr2)
	{
		while (arr2[arr2_len])
			++arr2_len;
	}
	length = malloc(sizeof(char *) * (arr1_len + arr2_len + 1));
	if (!length)
		return (NULL);

	result = 0;
	if (arr1)
	{
		while (*arr1)
			length[result++] = _strdup(*arr1++);
	}
	if (arr2)
	{
		while (*arr2)
			length[result++] = _strdup(*arr2++);
	}
	length[result] = NULL;
	return (length);
}

/**
 * arrdup - a function to dup an array
 * @arr: double array pointer
 *
 * Return: returns the dup array
 */
char **arrdup(char **arr)
{
	char **twin = NULL;
	size_t length = 0;

	if (!arr)
		return (NULL);
	while (arr[length++])
		;
	twin = malloc(sizeof(*twin) * length);
	if (!twin)
		return (NULL);
	while (length--)
		twin[length] = _strdup(arr[length]);
	return (twin);
}
