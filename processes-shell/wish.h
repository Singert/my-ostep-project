#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

extern char * error_message;
extern char * env[500];

void shell_start(char * batchfile);

int count_tokens(char * tokens, int char_count);

int read_line(char ** buffer, FILE * stream);

char ** tokenize(FILE * stream, int input_type);

void token_extract(char * source, char ** destination);

void exec_cmd(char ** commands);

void command_select(char ** commands, int token_count);

char * is_file_exist(char * path);

void path_init(char ** commands, int token_count);