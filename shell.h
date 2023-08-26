#ifndef HSH_H
#define HSH_H

#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>


#include "aka.h"
#include "bools.h"
#include "builtins.h"
#include "command.h"
#include "words.h"
#include "envar.h"
#include "err.h"
#include "info.h"
#include "lists.h"
#include "path.h"
#include "quotes.h"
#include "string.h"
#include "toks.h"
#include "typdef.h"

extern char **environ;

bool read_input(info_t *info);
char *expand_alias(alias_t *aliases, char ***tokptr);
char **_expand_vars(info_t *info, char ***tokptr);
int parse(info_t *info);
int execute(info_t *info);
int _execute(info_t *info);
quote_state_t _read_input(char **lineptr, int fd);
void expand_aliases(alias_t *aliases, char ***tokptr);
void expand_vars(info_t *info, char ***tokptr);
void open_script(info_t *info);
void remove_comments(cmdlist_t *cmd);
void _sigint(int signal);

#endif
