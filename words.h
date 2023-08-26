#ifndef _WORDS_H_
#define _WORDS_H_

#include <stdlib.h>

#include "string.h"
#include "typdef.h"

/**
  * struct dict - a function that prints a singly linked list
  * @key: main variable
  * @val: variable value
  * @next: pointer to next node
  */
struct dict
{
	char *key;
	char *val;
	struct dict *next;
};

char *get_dict_val(dict_t *head, const char *key);
dict_t *get_dict_node(dict_t *head, const char *key);
dict_t *add_dict_node_end(dict_t **headptr, const char *key, const char *val);
dict_t *del_dict_node(dict_t **headptr, const char *key);
void free_dict(dict_t **headptr);

#endif
