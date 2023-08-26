#include "quotes.h"

/**
 * quote_state - a function that retrieves state of given character
 * @c: char
 * Return: 0
 */
quote_state_t quote_state(char c)
{
	if (_isspace(c))
		return (QUOTE_NONE);
	if (c == '"')
		return (QUOTE_DOUBLE);
	if (c == '\'')
		return (QUOTE_SINGLE);
	if (c == '\\')
		return (QUOTE_ESCAPE);
	return (QUOTE_WORD);
}

/**
 * quote_state_f - a function that retrieves function of a given state
 * @s: the state
 * Return: state
 */
quote_state_fp quote_state_f(quote_state_t s)
{
	switch (s)
	{
		case QUOTE_NONE:
			return (_quote_state_none);
		case QUOTE_WORD:
			return (_quote_state_word);
		case QUOTE_DOUBLE:
			return (_quote_state_double);
		case QUOTE_SINGLE:
			return (_quote_state_single);
		case QUOTE_ESCAPE:
			return (_quote_state_escape);
	}
	return (0);
}
/**
 * quote_state_len - a function that outputs state's length
 * @str: pointer to string
 * @state: state
 * Return: state
 */
size_t quote_state_len(const char *str, quote_state_t state)
{
	return (quote_state_f(state)(str, 0));
}

/**
 * dequote - a function that unquotes a string
 * @str: pointer to string to unquote
 * Return: 0 if failed, else copy of dequoted string.
 */

char *dequote(const char *str)
{
	char *new_node;
	size_t length = 0, slen;
	quote_state_t state;

	if (str == 0)
		return (0);

	new_node = malloc(sizeof(char) * (dequote_len(str) + 1));
	if (new_node == 0)
		return (0);

	while (*str)
	{
		state = quote_state(*str);
		str += (1 && (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE)));
		slen = quote_state_len(str, state);
		if (state & QUOTE_DOUBLE)
		{
			for ( ; slen; --slen)
			{
				if (quote_state(*str++) & QUOTE_ESCAPE)
				{
					if (*str == '\n')
					{
						++str, --slen;
						continue;
					}
					if (_isspecial_double(*str))
						++str, --slen;
				}
				new_node[slen++] = str[-1];
			}
		}
		_memcpy(new_node + length, str, slen);
		length = length + slen;
		str = str + slen;
		str += (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)));
	}
	new_node[length] = '\0';
	return (new_node);
}


/**
 * dequote_len - a function that sums string length after dequoting
 * @str: pointer to string
 * Return: length
 */
size_t dequote_len(const char *str)
{
	size_t length = 0, slen;
	quote_state_t state;

	while (*str)
	{
		state = quote_state(*str);
		str += (1 && (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE)));
		slen = quote_state_len(str, state);
		if (state & QUOTE_DOUBLE)
		{
			for ( ; slen; --slen)
			{
				if (quote_state(*str++) & QUOTE_ESCAPE)
				{
					if (*str == '\n')
					{
						++str, --slen;
						continue;
					}
					if (_isspecial_double(*str))
						++str, --slen;
				}
				length++;
			}
		}
		length = length + slen;
		str = str + slen;
		str = str + (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)));
	}
	return (length);
}
