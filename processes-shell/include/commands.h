#ifndef COMMANDS
#define COMMANDS

#include "file_operations.h"
#include "tokens.h"


void command_select(char ** commands, int token_count);

int redirect_check(char ** single_command, int command_size);

int get_command_checkpoints(char ** commands, int token_count, int * checkpoints);

void exec_command(char ** commands, int * checkpoints, int checkpoints_count);



#endif