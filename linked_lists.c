#include "lists.h"

/**
 * str_to_list - a function that converts string into a linked list
 * @str: pointer to string
 * @delim: delimiter
 * Return: pointer to head of list
 */
list_t *str_to_list(const char *str, char delim)
{
	list_t *top = NULL;

	if (!str)
		return (NULL);

	if (!_str_to_list(&top, str, delim))
		free_list(&top);

	return (top);
}


/**
 * _str_to_list - a function that helps to convert strings to a linked list
 * @tailptr: pointer to tail
 * @str: pointer to string
 * @delim: delimiter
 * Return: pointer to list's tail
 */
list_t *_str_to_list(list_t **tailptr, const char *str, char delim)
{
	list_t *endlist;
	ssize_t size = _strchr(str, delim);

	if (size == -1)
		size = _strlen(str);

	endlist = add_node_end(tailptr, NULL);
	if (!endlist)
		return (NULL);

	endlist->str = _memdup(str, size + 1);
	if (!endlist->str)
		return (NULL);

	endlist->str[size] = '\0';

	if (str[size])
		return (_str_to_list(&endlist, str + size + 1, delim));

	return (endlist);
}


/**
 * add_node - a function that inserts a string at the start of the list
 * @headptr: pointer to the first list node address
 * @str: pointer to string
 * Return: 0 if failure, else new node's address
 */
list_t *add_node(list_t **headptr, const char *str)
{
	list_t *new_node;

	if (!headptr)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	new_node->str = _strdup(str);
	new_node->next = *headptr;

	*headptr = new_node;

	return (new_node);
}


/**
 * add_node_end - a function that adds string at list's end
 * @headptr: a double pointer
 * @str: pointer to string
 * Return: result
 */
list_t *add_node_end(list_t **headptr, const char *str)
{
	list_t *result;

	if (!headptr)
		return (NULL);

	if (*headptr)
		return (add_node_end(&((*headptr)->next), str));

	result = malloc(sizeof(list_t));
	if (!result)
		return (NULL);

	result->str = _strdup(str);
	result->next = *headptr;

	*headptr = result;

	return (result);
}


/**
 * free_list - a function that frees a linked list and set head to NULL
 * @headptr: a pointer to node's beginning
 */
void free_list(list_t **headptr)
{
	if (!*headptr)
		return;

	free_list(&((*headptr)->next));
	free((*headptr)->str);
	free(*headptr);
	*headptr = NULL;
}
