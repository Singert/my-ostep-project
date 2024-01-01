#include "../include/commands.h"

void command_select(char ** commands, int token_count){

    if(strcmp(commands[0], "exit") == 0 && token_count == 1){
        free_token_array(commands, token_count);
        exit(0);

    }else if(strcmp(commands[0], "cd") == 0){

        if(token_count != 2 || chdir(commands[1]) == -1){
            display_error();
            free_token_array(commands, token_count);
            exit(0);
        }

    }else if(strcmp(commands[0], "path") == 0){
        
        update_path(commands, token_count);

    }else{
        int checkpoints[100] = {0};
        int checkpoints_count = get_command_checkpoints(commands, token_count, checkpoints);
        exec_command(commands, checkpoints, checkpoints_count);
        
    }
}


int redirect_check(char ** single_command, int command_size){

    int redirect_count = 0;

    for (size_t i = 0; i <= command_size; i++)
    {
        if(strcmp(single_command[i], ">") == 0 && (i != command_size-1)){
            display_error();
            return -1;
        }

        if(strcmp(single_command[i], ">") == 0){
            redirect_count++;
        }
        
    }

    if(redirect_count > 1){
        display_error();
        return -1;
    }

    return redirect_count;

}



int get_command_checkpoints(char ** commands, int token_count, int * checkpoints){
    int j = 0;
    int f = 0;
    for (size_t i = 0; i < token_count; i++)
    {
        if((strcmp(commands[i], "&") == 0 && i!= token_count -1 && strcmp(commands[i], commands[i+1]) == 0) || strcmp(commands[0], "&") == 0){
            // fprintf(stderr, "%s", error_message);
            return -1;
        }

        if(strcmp(commands[i], "&") == 0){
            checkpoints[j++] = i - 1;
            f = 0;
            continue;
        }

        if(f == 0){
            checkpoints[j++] = i;
            f = 1;
        }
        
    }

    if(strcmp(commands[token_count - 1], "&") != 0){
        checkpoints[j++] = token_count - 1;
    }
    
    return j;
    
}


void exec_command(char ** commands, int * checkpoints, int checkpoints_count){

    if(commands == NULL || checkpoints_count == -1){
        return;
    }

    int j = 0;
    size_t * pid = (size_t *) malloc(sizeof(size_t) * (checkpoints_count/2));

    int original_stdout;
    int original_stderr;

    while(j < checkpoints_count){

        char * path;
        if((path = is_file_exist(commands[checkpoints[j]])) == NULL){
            display_error();
            free(path);
            free(pid);
            return;
        }

        int command_size = checkpoints[j+1] - checkpoints[j];
        char ** single_command = (char **) malloc(sizeof(char *) * (command_size + 2));

        size_t i;
        for (i = checkpoints[j]; i <= checkpoints[j+1]; i++)
        {
            single_command[i-checkpoints[j]] = commands[i];
        }
        single_command[i-checkpoints[j]] = '\0';
        
        int redirect_count = 0;

        if((redirect_count = redirect_check(single_command, command_size)) == -1){
            free(path);
            free(single_command);
            free(pid);
            return;

        }else if(redirect_count == 1){

            original_stdout = dup(1);
            original_stderr = dup(2);

            if(redirect_stdout_stderr(commands[checkpoints[j+1]]) == -1){
                display_error();
                free(path);
                free(single_command);
                free(pid);
                return;
            }
            single_command[command_size] = NULL;
            single_command[command_size-1] = NULL;
        }


        pid[j/2] = fork();

        if(pid[j/2] == -1){
            exit(1);
        }else if(pid[j/2] == 0){

            execv(path, single_command);
            display_error();
            exit(1);

        }

        if(redirect_count == 1){
            restore_stdout_stderr(original_stdout, original_stderr);
        }

        j+=2;
        free(single_command);
        free(path);
    }

    for (size_t i = 0; i < checkpoints_count/2; i++)
    {
        waitpid(pid[i], NULL, 0);
    }

    free(pid);
    
}