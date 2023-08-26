#ifndef _ENVAR_H_
#define _ENVAR_H_

#include <stdlib.h>
#include "words.h"
#include "string.h"
#include "typdef.h"

typedef dict_t env_t;

char **dict_to_env(env_t *head);
env_t *env_to_dict(char **env);
env_t *_env_to_dict(env_t **tailptr, char **env);

#endif
