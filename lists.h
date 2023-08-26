#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>
#include "string.h"
#include "typdef.h"

/**
 * struct list - creates struct singly linked list data type
 * @str: pointer to string
 * @next: pointer to next
 */
struct list
{
	char *str;
	struct list *next;
};

list_t *str_to_list(const char *str, char delim);
list_t *_str_to_list(list_t **tailptr, const char *str, char delim);
list_t *add_node(list_t **headptr, const char *str);
list_t *add_node_end(list_t **headptr, const char *str);
void free_list(list_t **headptr);

#endif
