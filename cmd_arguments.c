#include "command.h"

/**
 * cmd_to_list - a func to tokenize the command
 * @cmd: a command ptr
 * Return: returns a NULL or a ptr
 */
cmdlist_t *cmd_to_list(const char *cmd)
{
	cmdlist_t *top = 0;
	size_t sum;
	char *split = _strdup(cmd);

	if (split == 0)
		return (0);

	sum = split_cmd(split);
	if (_cmd_to_list(&top, split, sum) == 0)
	{
		free_cmdlist(&top);
		return (0);
	}
	free(split);
	return (top);
}

/**
 * _cmd_to_list - a function outputs linked list of tokenized cmd
 * @tailptr: ptr to the end of cmdlist
 * @split: splits the list
 * @count: the splited lists addition
 *
 * Return: returns 0 or NULL
 */

cmdlist_t *_cmd_to_list(cmdlist_t **tailptr, char *split, size_t count)
{
	cmdlist_t *end;

	if (count == 0)
		return (*tailptr);

	end = add_cmd_end(tailptr, split);
	if (end == 0)
		return (0);
	while (*split++)
		;
	return (_cmd_to_list(&end, split, count - 1));
}


/**
 * cmd_to_tree - function to output commands binary tree
 * @tokens: command to print
 *
 * Return: returns null or output
 */
cmdtree_t *cmd_to_tree(const char * const *tokens __attribute__((unused)))
{
	return (0);
}

/**
 * free_cmdtree - function frees the binary tree
 * @rootptr: double ptr
 * Return: returns a NULL ptr
 */
void free_cmdtree(cmdtree_t **rootptr)
{
	if (rootptr && *rootptr)
	{
		free_cmdtree(&((*rootptr)->success));
		free_cmdtree(&((*rootptr)->failure));
		(*rootptr)->tokens = NULL;
		(*rootptr) = NULL;
	}
}
