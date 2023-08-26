#ifndef PATH_H
#define PATH_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "string.h"
#include "typdef.h"
#include "info.h"
#include "lists.h"

char *search_path(info_t *info, list_t *path);

#endif
