#include "quotes.h"

/**
 * _quote_state_none - a function that retrieves length of state and it's next
 * @str: pointer to string
 * @state: pointer to state
 *
 * Return: the state length
 */
size_t _quote_state_none(const char *str, quote_state_t *state)
{
	size_t length = 0;

	while (_isspace(*str))
		++str, ++length;
	if (state && *str)
		*state = quote_state(*str);
	return (length);
}


/**
 * _quote_state_word - Entry point to the function
 * @str: pointer to string
 * @state: pointer to state
 * Return: length
 */
size_t _quote_state_word(const char *str, quote_state_t *state)
{
	size_t length = 0;

	while (*str && _isspace(*str) == 0 && _isquote(*str) == 0)
		++str, length++;
	if (state && *str)
		*state = quote_state(*str);
	return (length);
}


/**
 * _quote_state_double - Entry point to function
 * @str: pointer to string
 * @state: pointer to state
 * Return: length
 */
size_t _quote_state_double(const char *str, quote_state_t *state)
{
	size_t length = 0;

	while (*str && *str != '"')
		str++, length++;
	if (state && *str)
		*state = quote_state(*(str + 1));
	return (length);
}


/**
 * _quote_state_single - a function that prints state length
 * @str: pointer to string
 * @state: pointer to state
 * Return: length
 */
size_t _quote_state_single(const char *str, quote_state_t *state)
{
	size_t length = 0;

	while (*str && *str != '\'')
		str++, length++;
	if (state && *str)
		*state = quote_state(*(str + 1));
	return (length);
}


/**
 * _quote_state_escape - a function that prints state length
 * @str: pointer to string
 * @state: pointer to state
 * Return: 0
 */
size_t _quote_state_escape(const char *str, quote_state_t *state)
{
	if (*str)
	{
		if (state && *(++str))
			*state = quote_state(*str);
		return (1);
	}
	return (0);
}

