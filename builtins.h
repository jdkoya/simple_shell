#ifndef _BUILTINS_H_
#define _BUILTINS_H_

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "aka.h"
#include "envar.h"
#include "err.h"
#include "info.h"
#include "path.h"
#include "string.h"
#include "typdef.h"

#define ALIAS_HELP "alias [KEY[=VALUE] ...]"
#define ALIAS_DESC                                                          \
	"Define and shows aliases.\n\0"                                     \
	"Display existing aliases if no arguments.\0"                       \
	"Else, define an alias for each KEY=VALUE pair provided.\0"         \
	"Display for each KEY with no VALUE, the corresponding alias.\0"    \
	"The next word will be expanded if VALUE ends with a space.\0"      \
	"\0"

#define CD_HELP "cd [DIR]"
#define CD_DESC                                                             \
	"Changes the current working directory to DIR.\n\0"                 \
	"If DIR is omitted, resets to the value of the variable HOME.\0"    \
	"If DIR is -, the current directory returns to initial value.\0"    \
	"\0"

#define ENV_HELP "env"
#define ENV_DESC                                                            \
	"Prints the environment.\0"                                         \
	"\0"

#define EXEC_HELP "exec COMMAND [ARGS ...]"
#define EXEC_DESC                                                           \
	"Replace the shell with the given command.\n\0"                     \
	"COMMAND is executed, replacing the executing shell.\0"             \
	"ARGS are passed as positional arguments to COMMAND.\0"             \
	"If the command cannot be executed, the shell exits.\0"             \
	"\0"

#define EXIT_HELP "exit [STATUS]"
#define EXIT_DESC                                                            \
	"Exit the shell with STATUS.\n\0"                                       \
	"If STATUS is omitted, the exit status of the last command remains.\0"  \
	"\0"

#define HELP_HELP "help [BUILTIN]"
#define HELP_DESC                                                             \
	"Display builtin commands' information.\n\0"                          \
	"If BUILTIN is excluded, the available commands are displayed.\0"     \
	"\0"
#define SETENV_HELP "setenv [NAME [VALUE]]"
#define SETENV_DESC                                                           \
	"Sets environment variable NAME to VALUE.\n\0"                        \
	"If NAME is not added, display the shell execution environment.\0"     \
	"If VALUE is excluded, the value of NAME is set to an empty string.\0"  \
	"\0"

#define UNSETENV_HELP "unsetenv NAME"
#define UNSETENV_DESC                                                        \
	"Deletes the variable NAME from the environment.\0"                  \
	"\0"

typedef int (*builtin_fp)(info_t *);

/**
 * struct builtin - the builtin command structure
 * @name: name of the command
 * @f: func call
 * @help: command uses
 * @desc:  commands descriptor
 */
struct builtin
{
	const char *name;
	builtin_fp f;
	const char *help;
	const char *desc;
};

const struct builtin *get_builtin(const char *name);
const struct builtin *get_builtins(void);

int __alias(info_t *info);
int __cd(info_t *info);
int __env(info_t *info);
int __exec(info_t *info);
int __exit(info_t *info);
int __help(info_t *info);
int __history(info_t *info);
int __setenv(info_t *info);
int __unsetenv(info_t *info);

#endif
