#include "shell.h"

void _sigint(int signal __attribute__((unused)));
int parse(info_t *info);

/**
 * main - This is the main fuction of the programme
 * @argc: argument count
 * @argv: pointer to argument vector
 * Return: 0
 */
int main(int argc, char **argv)
{
	info_t *info = init_info(argc, argv);

	signal(2, _sigint);

	while (read_input(info))
	{
		parse(info);
		while ((info->tokens = pop_cmd(&(info->commands))))
		{
			execute(info);
			free_tokens(&(info->tokens));
		}
		free(info->line);
		info->line = NULL;
	}
	if (info->interactive)
		write(STDOUT_FILENO, "\n", 1);

	if (info->file)
		close(info->fileno);

	exit(free_info(info));
}


/**
 * parse - A function that parses user input
 * @info: shell information
 * Return: sum
 */
int parse(info_t *info)
{
	char **tokens, *toke;
	size_t num = 0;
	cmdlist_t *cmd = info->commands = cmd_to_list(info->line);

	while (cmd)
	{
		remove_comments(cmd);
		if (!cmd->tokens)
		{
			cmd = cmd->next;
			del_cmd(&(info->commands), num);
			continue;
		}
		expand_aliases(info->aliases, &(cmd->tokens));
		if (!cmd->tokens)
		{
			cmd = cmd->next;
			del_cmd(&(info->commands), num);
			continue;
		}
		expand_vars(info, &(cmd->tokens));
		if (!cmd->tokens)
		{
			cmd = cmd->next;
			del_cmd(&(info->commands), num);
			continue;
		}
		tokens = cmd->tokens;
		for (toke = *tokens; toke; toke = *(++tokens))
		{
			*tokens = dequote(toke);
			free(toke);
		}
		cmd = cmd->next;
		++num;
	}
	return (num);
}


/**
  * _sigint - a function that repeats shell prompt
  * @signal: input variable
  */
void _sigint(int signal __attribute__((unused)))
{
	fflush(STDIN_FILENO);
	write(STDERR_FILENO, "\n$ ", 3);
}
