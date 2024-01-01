#ifndef COMMANDS
#define COMMANDS

#include "file_operations.h"
#include "tokens.h"


void command_select(char ** commands, int token_count);

int get_command_checkpoints(char ** commands, int token_count, int * checkpoints);

void exec_command(char ** commands, int * checkpoints, int checkpoints_count);

void exec_single_command(char ** single_command, char * path, int checkpoint_index, size_t * pid);

int handle_redirection(char **single_command, int command_size, int checkpoint_index, int * original_stdout, int * original_stderr);

char **get_single_command(char **commands, int *checkpoints, int checkpoint_index, int command_size);

void free_resources(char **single_command, char *path);

void wait_for_child_processes(size_t * pid, int checkpoints_count);

int redirect_check(char ** single_command, int command_size);

#endif