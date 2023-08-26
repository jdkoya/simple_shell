#include "builtins.h"
#include "err.h"
#include "shell.h"
#include "getline.h"
#include <stdio.h>

/**
  * perrorl - func to output formatted message to stderr
  * @msg: the error message to print
  * @...: output
  */
void perrorl(const char *msg, ...)
{
	const char *str;
	va_list result;

	va_start(result, msg);
	while ((str = va_arg(result, char *)))
	{
		write(STDERR_FILENO, str, _strlen(str));
		write(STDERR_FILENO, ": ", 2);
	}
	va_end(result);

	if (msg)
		write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}


/**
  * perrorl_default - func output formatted message to stderr
  * @arg0: is an arg
  * @lineno: line number
  * @msg: error message to print
  * @...: output
  */

void perrorl_default(const char *arg0, size_t lineno, const char *msg, ...)
{
	char *strless = num_to_str(lineno);
	const char *str = 0;
	va_list m;

	if (arg0)
		write(STDERR_FILENO, arg0, _strlen(arg0));
	write(STDERR_FILENO, ": ", 2);

	if (strless)
		write(STDERR_FILENO, strless, _strlen(strless));
	write(STDERR_FILENO, ": ", 2);

	va_start(m, msg);
	while ((str = va_arg(m, char *)))
	{
		write(STDERR_FILENO, str, _strlen(str));
		write(STDERR_FILENO, ": ", 2);
	}
	va_end(m);

	if (msg)
		write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	free(strless);
}


/**
 * atou - func converts a string to an int
 * @s: is the char to check
 * Return: int
 */
unsigned int atou(char *s)
{
	size_t i;
	unsigned int num = 0;
	unsigned int sum;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (UINT_MAX / 10 < num)
			return (UINT_MAX);
		num *= 10;
		sum = s[i] - '0';
		if (UINT_MAX - sum < num)
			return (UINT_MAX);
		num = num + sum;

	}
	return (num);
}


/**
 * read_input - get input
 * @info: shell information
 *
 * Return: line size
 */
bool read_input(info_t *info)
{
	char *line = 0, *temp = 0;

	if (info->interactive)
		write(STDERR_FILENO, "$ ", 2);

	(*info).lineno += 1;
	while (_read_input(&info->line, (*info).fileno) &
		(QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
	{
		temp = line;
		line = strjoin(0, "", temp, (*info).line);
		free(temp);
		free((*info).line);
		if ((*info).interactive)
			write(STDERR_FILENO, "> ", 2);
		(*info).lineno += 1;
	}
	if (line)
	{
		temp = (*info).line;
		(*info).line = strjoin(0, "", line, temp);
		free(temp);
		free(line);
	}
	return ((*info).line);
}


/**
 * _read_input - read a single line
 * @lineptr: line buffer
 * @fd: file descriptor to read from
 *
 * Return: ending quote state
 */

quote_state_t _read_input(char **lineptr, int fd)
{
	char *line = *lineptr = _getline(fd);
	static quote_state_t state = QUOTE_NONE;
	size_t index = 0;

	if (line)
	{
		switch (state & (QUOTE_DOUBLE | QUOTE_SINGLE))
		{
		case QUOTE_DOUBLE:
		case QUOTE_SINGLE:
			do {
				index += quote_state_len(line + index, state);
				if (line[index] == '\0')
					continue;
				if (state & (QUOTE_DOUBLE | QUOTE_SINGLE))
					index += 1;
				/* fall through */
		case 0:
				state = quote_state(line[index]);
				if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
					index = index + 1;
			} while (line[index]);
		}
	}
	return (state);
}
