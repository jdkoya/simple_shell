#include "bools.h"

/**
 * _isalpha - function to check alphabetic chars
 * @c: stands for chars to check
 * Return: returns 1 if c prints letters, else display 0
 */
bool _isalpha(int c)
{
	return ((c >= 97 && c <= 122) || (c >= 65 && c <= 90));
}

/**
 * _isdigit -function to output digit ranges from 0-9
 * @c: checks value
 * Return: returns c valur or integer
 */
bool _isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

/**
  * _isalnum - alphanumeric of a char function checker
  * @c: input value
 * Return: returns 1 or 0
  */
bool _isalnum(int c)
{
	return (_isalpha(c) || _isdigit(c));
}

/**
  * _isident - Entry to program
  * @c: value
  * Return: returns 1 or 0
  */
bool _isident(int c)
{
	return (c == '_' || _isalnum(c));
}

/**
  * _isnumber - checks for num only in a string
  * @s: ptr
  * Return: returns true or false outcome
  */
bool _isnumber(const char *s)
{
	if (s)
	{
		while (*s)
		{
			if (!_isdigit(*s++))
				return (false);
		}
		return (true);
	}
	return (false);
}
