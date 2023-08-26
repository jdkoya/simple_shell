#ifndef _PAST_H_
#define _PAST_H_

#include "lists.h"
#include "typdef.h"

/**
  * struct history - a function that prints shell history
  * @head: pointer to list
  * @filename: pointer to files archive names
  * @n: the number of list entries
  */
struct history
{
	struct list *head;
	char *filename;
	size_t n;
};

#endif
