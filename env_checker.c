#include "envar.h"

/**
  * env_to_dict - a func that generates list from the environ
  * @env: the argument input
  * Return: returns a ptr start
  */
env_t *env_to_dict(char **env)
{
	env_t *start = 0;

	if (_env_to_dict(&start, env) == 0)
		free_dict(&start);

	return (start);
}


/**
 * _env_to_dict - a helper func that replaces env for linked list
 * @tailptr: a pointer to list tail
 * @env: input
 *
 * Return: ...
 */
env_t *_env_to_dict(env_t **tailptr, char **env)
{
	env_t *end;
	char *str;
	ssize_t len;

	if (*env == 0)
		return (*tailptr);

	str = _strdup(*env);
	if (str == 0)
		return (0);

	len = _strchr(*env, '=');

	if (len == -1)
		return (0);

	str[len] = '\0';
	end = add_dict_node_end(tailptr, str, len + str + 1);
	free(str);

	return (_env_to_dict(&end, env + 1));
}


/**
  * dict_to_env - func that outputs a linked list from environ
  * @head: head ptr of list
  * Return: linked list ptr
  */
char **dict_to_env(env_t *head)
{
	char **env;
	size_t len = 0;
	env_t *temp = head;

	while (temp)
		len++, temp = (*temp).next;

	env = malloc(sizeof(char *) * (len + 1));
	if (env == 0)
		return (0);

	for (len = 0; head; head = head->next)
		env[len++] = strjoin(0, "=", (*head).key, (*head).val);
	env[len] = 0;

	return (env);
}
