#include "shell.h"

/**
  * execute -  commands execution function
  * @info:  input command or data
  *
  * Return: ...
  */
int execute(info_t *info)
{
	const builtin_t *b = get_builtin(*info->tokens);

	if (b)
	{
		return (b->f(info));
	}
	if (_strchr(*info->tokens, '/') == -1)
	{
		free_list(&info->path);
		info->path = str_to_list(get_dict_val(info->env, "PATH"), ':');
		info->exe = search_path(info, info->path);
	}
	else
	{
		info->exe = _strdup(*info->tokens);
	}
	if (info->exe && access(info->exe, X_OK) == 0)
	{
		return (_execute(info));
	}
	if (info->exe)
	{
		perrorl_default(*info->argv, info->lineno, "Access denied",
				*info->tokens, NULL);
		info->status = 126;
	}
	else
	{
		perrorl_default(*info->argv, info->lineno, "not found",
				*info->tokens, NULL);
		info->status = 127;
	}
	return (info->status);
}

/**
 * _execute - a func to fork and execute the current cmd
 * @info: pointer to input command
 *
 * Return: returns the exit status child process
 */
int _execute(info_t *info)
{
	char *exe, **argv, **env;

	switch (fork())
	{
	case 0:
		exe = info->exe;
		argv = info->tokens;
		env = dict_to_env(info->env);

		info->exe = NULL;
		info->tokens = NULL;
		free_info(info);

		execve(exe, argv, env);
		perror(*argv);

		if (info->file)
			close(info->fileno);

		free(exe);
		free_tokens(&argv);
		free_tokens(&env);
		exit(EXIT_FAILURE);
		break;
	case -1:
		perrorl_default(*info->argv, info->lineno, "Can't fork", NULL);
		info->status = 2;
		break;
	default:
		wait(&info->status);
		info->status = WEXITSTATUS(info->status);
		break;
	}
	free(info->exe);
	info->exe = NULL;

	return (info->status);
}
