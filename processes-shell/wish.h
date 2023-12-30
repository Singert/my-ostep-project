#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

extern char * error_message;
extern char * env[500];
extern int env_count;

void shell_start(char * batchfile);

int count_tokens(char * tokens, int char_count);

int read_line(char ** buffer, FILE * stream);

void tokenize(FILE * stream, int input_type);

void token_extract(char * source, char ** destination, char * delim);

void exec_cmd(char ** commands, int * checkpoints, int checkpoints_count);

void command_select(char ** commands, int token_count);

char * is_file_exist(char * path);

void path_init(char ** commands, int token_count);

int tokenize_commands(char ** commands, int token_count, int * checkpoints);

int redirect_start(char * filename);

void redirect_end(int original_stdout, int original_stderr);

char * token_trim(char * token, int start, int end);

void free_token_array(char ** token_array, int length);