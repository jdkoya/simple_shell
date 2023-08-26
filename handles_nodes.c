#include "words.h"

/**
  * get_dict_val - retrieves values from a dictionary
  * @head: is a ponter
  * @key: input value
  *
  * Return: a ptr to the key
  */
char *get_dict_val(dict_t *head, const char *key)
{
	if (key == 0)
		return (0);

	while (head)
	{
		if (!_strcmp((*head).key, key))
			return ((*head).val);
		head = (*head).next;
	}

	return (0);
}


/**
  * get_dict_node - function prints a node by key
  * @head: is a ptr
  * @key: entry value
  *
  * Return: NULL or printed node
  */
dict_t *get_dict_node(dict_t *head, const char *key)
{
	if (head == 0)
		return (0);
	if (_strcmp((*head).key, key) == 0)
		return (head);
	return (get_dict_node((*head).next, key));
}


/**
  * add_dict_node_end - function adds node at the end of a list
  * @headptr: is a pointer
  * @key: input
  * @val: entry value
  * Return: ptr to the list
  */
dict_t *add_dict_node_end(dict_t **headptr, const char *key, const char *val)
{
	dict_t *new_node;

	if (headptr == 0)
		return (0);

	if (*headptr)
		return (add_dict_node_end(&((*headptr)->next), key, val));

	new_node = malloc(sizeof(dict_t));
	if (new_node == 0)
		return (0);

	(*new_node).key = _strdup(key);
	(*new_node).val = _strdup(val);
	(*new_node).next = NULL;

	*headptr = new_node;
	return (new_node);
}

/**
  * del_dict_node - function that deletes a node
  * @headptr: pointer value
  * @key: input
  *
  * Return: pointer to the output list
  */
dict_t *del_dict_node(dict_t **headptr, const char *key)
{
	dict_t *temp;

	if  ((headptr && *headptr) == 0)
		return (0);
	if (!_strcmp((*headptr)->key, key))
	{
		temp = *headptr;
		(*headptr) = (*temp).next;
		free((*temp).key);
		free((*temp).val);
		free(temp);
	}
	else
		del_dict_node(&((*headptr)->next), key);
	return (*headptr);
}


/**
 * free_dict - frees a linked list
 * @headptr: beginning of the list node
 */
void free_dict(dict_t **headptr)
{
	if (*headptr == 0)
		return;

	free_dict(&((*headptr)->next));
	free((*headptr)->key);
	free((*headptr)->val);
	free(*headptr);
	*headptr = 0;
}
