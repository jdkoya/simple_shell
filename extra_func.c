#include "bools.h"
#include "quotes.h"
/**
 * _isquote - A function that checks if input char is a quote
 * @a: user input
 * Return: 1 if successful, else 0
 */
bool _isquote(int a)
{
	return (a == '"' || a == '\'' || a == '\\');
}

/**
 * _isspace - a function that prints a space
 * @a: value
 * Return: 1 if successful, else 0
 */
bool _isspace(int a)
{
	return (a == ' ' || (a >= 0x09 && a <= 0x0d));
}

/**
 * _isspecial_double - a that function checks double special chars
 * @a: a character
 * Return: 1 if successful, else 0
 */

int _isspecial_double(char a)
{
	return (a == '"' || a == '$' || a == '\\');
}
