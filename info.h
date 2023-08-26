#ifndef _INFO_H_
#define _INFO_H_

#include <stdlib.h>
#include <unistd.h>

#include "aka.h"
#include "command.h"
#include "envar.h"
#include "err.h"
#include "getline.h"
#include "past.h"
#include "lists.h"
#include "string.h"
#include "toks.h"
#include "typdef.h"

extern char **environ;

/**
  * struct info - shell state
  * @interactive: user input
  * @argc: user input
  * @argv: user input
  * @file: user input
  * @fileno: user input
  * @status: user input
  * @line: user input
  * @lineno: user input
  * @tokens: user input
  * @pid: user input
  * @cwd: user input
  * @exe: user input
  * @env: user input
  * @path: user input
  * @aliases: user input
  * @history: user input
  * @commands: user input
  */
struct info
{
	int interactive;
	int argc;
	char **argv;
	char *file;
	int fileno;
	int status;
	char *line;
	size_t lineno;
	char **tokens;
	pid_t pid;
	char *cwd;
	char *exe;
	env_t *env;
	list_t *path;
	alias_t *aliases;
	history_t *history;
	cmdlist_t *commands;
};

info_t *init_info(int argc, char **argv);
int free_info(info_t *info);

#endif
