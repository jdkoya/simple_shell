#include "shell.h"

/**
 * remove_comments - a function that handles comments
 * @cmd: pointer
 */
void remove_comments(cmdlist_t *cmd)
{
	char **tokens = cmd->tokens;
	char **print;
	char *temp;

	while (*tokens)
	{
		if (**tokens == '#')
		{
			temp = *tokens;
			*tokens = NULL;
			print = arrdup(cmd->tokens);
			*tokens = temp;
			free_tokens(&(cmd->tokens));
			cmd->tokens = print;
			free_cmdlist(&(cmd->next));
			return;
		}
		tokens++;
	}
}
