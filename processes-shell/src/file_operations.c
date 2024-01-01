#include "../include/file_operations.h"

int redirect_stdout_stderr(char * filename){

    int fd = open(filename, O_WRONLY|O_TRUNC|O_CREAT, 0644);

    if (fd < 0) {
        display_error();
        return -1;
    }

    if (dup2(fd, 1) < 0){
        display_error();
        return -1; 
    }

    if (dup2(fd, 2) < 0){
        display_error();
        return -1; 
    }

    close(fd);
    return 0;
}

void restore_stdout_stderr(int original_stdout, int original_stderr){
    
    if(dup2(original_stdout, 1) < 0){
        display_error();
        return; 
    }

    if(dup2(original_stderr, 2) < 0){
        display_error();
        return; 
    }

    close(original_stdout);
    close(original_stderr);
}

char * is_file_exist(char * filename){

    for (size_t i = 0; env[i] != NULL; i++)
    {
        char path[100]; 

        snprintf(path, sizeof(path), "%s/%s", env[i], filename);

        if (access(path, X_OK) == 0) {

            return strdup(path);
        }
    }
    
    return NULL;
    
}