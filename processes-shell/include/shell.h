#ifndef SHELL
#define SHELL

#include "commands.h"

FILE * shell_init(char * batchfile);

void shell_start(FILE * stream);

#endif