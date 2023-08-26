#include "path.h"


/**
* search_path - function to tokenize a command
* @info: argument value
* @path: path argument
* Return: returns null
*/
char *search_path(info_t *info, list_t *path)
{
	char *newpath, *cmd = *info->tokens;
	struct stat sb;

	while (path)
	{
		if (*path->str == '\0')
			newpath = strjoin(NULL, "/", info->cwd, cmd);
		else
			newpath = strjoin(NULL, "/", path->str, cmd);
		if (stat(newpath, &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) != S_IFDIR)
				return (newpath);
		}
		free(newpath);
		path = path->next;
	}
	return (NULL);
}
