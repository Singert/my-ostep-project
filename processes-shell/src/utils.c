#include "../include/utils.h"

void display_error(void){
    char * error_message = "An error has occurred\n";
    fprintf(stderr, "%s", error_message);
}

void initialize_path(void){
    env[0] = "/bin";
    env[1] = NULL;
}

void update_path(char ** commands, int token_count){
    // Each invokation of this function the environment variable gets erased and overwritten.
    memset(env, 0, sizeof(env));

    int i = 1;
    while(i < token_count){
        env[i-1] = strdup(commands[i]);
        i++;
    }

}

int read_input_line(char ** buffer, FILE * stream){
    size_t len = 0;
    int read = 0;

    read = getline(buffer, &len, stream);

    return read;
}

void free_token_array(char ** token_array, int length){
    for (size_t i = 0; i < length; i++){
        free(token_array[i]);
    }
    free(token_array);
}