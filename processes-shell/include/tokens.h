#ifndef TOKENS
#define TOKENS

#include "utils.h"

int count_tokens(char * tokens, int char_count);

void extract_token(char * source, char ** destination, char * delim);

char * trim_token(char * token, int start, int end);

#endif