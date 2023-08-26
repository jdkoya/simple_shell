#include "builtins.h"

/**
  * __exit - exit builtin function that exits the shell
  * @info: user input
  * Return: 0
  */
int __exit(info_t *info)
{
	char **built = (*info).tokens + 1;

	if (*built)
	{
		if (_isnumber(*built) && atou(*built) <= INT_MAX)
		{
			(*info).status = atou(*built);
		}
		else
		{
			perrorl_default(*info->argv, (*info).lineno, *built,
					*info->tokens, "Illegal number", 0);
			(*info).status = 2;

			return ((*info).status);
		}
	}
	if ((*info).file)
		close((*info).fileno);

	exit(free_info(info));
}

/**
  * __env - customised enc function prints the environment
  * @info: user input
  * Return: 0
  */
int __env(info_t *info)
{
	env_t *ven;

	(*info).status = EXIT_SUCCESS;

	for (ven = (*info).env; ven; ven = (*ven).next)
	{
		if ((*ven).key)
			write(STDOUT_FILENO, (*ven).key, _strlen((*ven).key));
		write(STDOUT_FILENO, "=", 1);
		if ((*ven).val)
			write(STDOUT_FILENO, (*ven).val, _strlen(ven->val));
		write(STDOUT_FILENO, "\n", 1);
	}
	return ((*info).status);
}


/**
 * __exec - customised exec function
 * @info: user input
 * Return: 0
 */
int __exec(info_t *info)
{
	char *exe;
	char **args = (*info).tokens + 1, **env = 0;

	if (!*args)
		return ((info->status = EXIT_SUCCESS));

	info->tokens = args;
	args = arrdup(args);

	if (_strchr(*args, '/') == -1)
	{
		free_list(&info->path);
		(*info).path = str_to_list(get_dict_val(info->env, "PATH"), ':');
		exe = search_path(info, info->path);
	}
	else
	{
		exe = _strdup(*args);
	}
	info->tokens -= 1;

	if (!access(exe, X_OK))
	{
		env = dict_to_env(info->env);

		free_info(info);
		execve(exe, args, env);
		perrorl_default(*info->argv, (*info).lineno, "Not found",
				*info->tokens, *args, 0);
		free(exe);
		free_tokens(&args);
		free_tokens(&env);
		exit(127);
	}
	perrorl_default(*info->argv, (*info).lineno, "Permission denied",
			*info->tokens, *args, 0);
	free(exe);
	free_tokens(&args);
	free_info(info);
	exit(126);
}

/**
 * __help - customised helper function for builtins commands
 * @info: struct info
 * Return: 0
 */
int __help(struct info *info)
{
	const builtin_t *bp = 0;
	char * const *args = info->tokens + 1;
	const char *desc = 0;
	size_t l = 0;

	if (*args)
	{
		info->status = EXIT_FAILURE;
		while (*args)
		{
			bp = get_builtin(*args);
			if (bp)
			{
				write(STDOUT_FILENO, (*bp).name, _strlen(bp->name));
				write(STDOUT_FILENO, ": ", 2);
				write(STDOUT_FILENO, (*bp).help, _strlen(bp->help));
				write(STDOUT_FILENO, "\n", 1);
				for (desc = (*bp).desc; (l = _strlen(desc)); desc += l + 1)
				{
					write(STDOUT_FILENO, "    ", 4);
					write(STDOUT_FILENO, desc, l);
					write(STDOUT_FILENO, "\n", 1);
				}
				(*info).status = EXIT_SUCCESS;
			}
			args = args + 1;
		}
		if ((*info).status == EXIT_FAILURE)
			perrorl_default(*info->argv, info->lineno, "No topics match",
					*info->tokens, *(args - 1), 0);
		return (info->status);
	}
	info->status = EXIT_SUCCESS;
	for (bp = get_builtins(); (*bp).name; bp += 1)
	{
		write(STDOUT_FILENO, (*bp).help, _strlen(bp->help));
		write(STDOUT_FILENO, "\n", 1);
	}
	return ((*info).status);
}
