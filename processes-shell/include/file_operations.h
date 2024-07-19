#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include "utils.h"

int redirect_stdout_stderr(char * filename);

void restore_stdout_stderr(int original_stdout, int original_stderr);

char * is_file_exist(char * path);

#endif