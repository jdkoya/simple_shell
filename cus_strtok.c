#include "toks.h"

/**
 * count_tokens - a function that checks strlen after dequoting
 * @str: pointer to string
 * Return: string length
 */
size_t count_tokens(const char *str)
{
	size_t sum = 0;
	quote_state_t state;

	for (; *(str += quote_state_len(str, QUOTE_NONE)); sum++)
	{
		while (*str && (state = quote_state(*str)) != QUOTE_NONE)
		{
			if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				str += quote_state_len(str + 1, state) + 1;
			else
				str = str + quote_state_len(str, state);

			if (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)))
				str++;
		}
	}
	return (sum);
}

/**
 * count_tokens_noquote - a function that counts the words in a string
 * @str: pointer to string
 * Return: -1 if string is NULL, else number of tokenized strings
 */
size_t count_tokens_noquote(const char *str)
{
	size_t total = 0;

	for (; *str; total++)
	{
		while (_isspace(*str))
			++str;
		if (*str == 0)
			break;
		do {
			++str;
		} while (*str && !_isspace(*str));
	}
	return (total);
}

/**
 * tokenize - a function that prints dequoted tokens
 * @str: pointer to string
 * Return: 0 if failed else return an array of string
 */

char **tokenize(const char *str)
{
	quote_state_t state;
	char **tokes;
	const char *tk;
	size_t sum;

	if (!str)
		return (0);

	tokes = malloc(sizeof(char *) * (count_tokens(str) + 1));
	if (tokes == 0)
		return (0);

	for (sum = 0; *(str += quote_state_len(str, QUOTE_NONE)); sum++)
	{
		tk = str;

		while (*str && (state = quote_state(*str)) != QUOTE_NONE)
		{
			if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
				str += quote_state_len(str + 1, state) + 1;
			else
				str = str + quote_state_len(str, state);

			if (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)))
				str++;
		}

		tokes[sum] = _memdup(tk, str - tk + 1);
		if (!tokes[sum])
		{
			free_tokens(&tokes);
			return (0);
		}
		tokes[sum][str - tk] = '\0';
	}
	tokes[sum] = 0;

	return (tokes);
}

/**
 * tokenize_noquote - a function that tokenise a string
 * @str: pointer to string
 * Return: 0 if failed else return an array of string
 */
char **tokenize_noquote(const char *str)
{
	char **tokes;
	const char *tk;
	size_t sum;

	if (str == 0)
		return (0);

	tokes = malloc(sizeof(char *) * (count_tokens_noquote(str) + 1));
	if (tokes == 0)
		return (0);

	for (sum = 0; *str; sum++)
	{
		while (_isspace(*str))
			++str;
		if (*str == 0)
			break;

		tk = str;
		do {
			++str;
		} while (*str && !_isspace(*str));

		tokes[sum] = _memdup(tk, str - tk + 1);
		if (!tokes[sum])
		{
			free_tokens(&tokes);
			return (0);
		}
		tokes[sum][str - tk] = '\0';
	}
	tokes[sum] = 0;

	return (tokes);
}

/**
 * free_tokens - a function that frees an array of strings
 * @tokens: double pointer
 */
void free_tokens(char ***tokens)
{
	char **tk;

	if (tokens == 0)
		return;

	tk = *tokens;
	if (tk == 0)
		return;

	while (*tk)
		free(*tk++);
	free(*tokens);

	*tokens = 0;
}
