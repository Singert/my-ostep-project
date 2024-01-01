#ifndef UTILS
#define UTILS

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

void display_error(void);

void initialize_path(void);

void update_path(char ** commands, int token_count);

int read_input_line(char ** buffer, FILE * stream);

void free_token_array(char ** token_array, int length);



#endif