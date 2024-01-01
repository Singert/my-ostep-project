#include "../include/commands.h"

/**
 * Select whether the command to be executed is built-in or not and proceeds to the execution.
*/
void command_select(char ** commands, int token_count){
    // Handle built-in commands
    if(strcmp(commands[0], "exit") == 0 && token_count == 1){
        free_token_array(commands, token_count);
        exit(0);
    }
    else if(strcmp(commands[0], "cd") == 0){
        if(token_count != 2 || chdir(commands[1]) == -1){
            display_error();
            free_token_array(commands, token_count);
            exit(0);
        }
    }
    else if(strcmp(commands[0], "path") == 0){
        update_path(commands, token_count);
    }
    else{
        // Handle external commands
        int checkpoints[100] = {0};
        int checkpoints_count = get_command_checkpoints(commands, token_count, checkpoints);
        exec_command(commands, checkpoints, checkpoints_count);
    }
}

/**
 * Execute the command statement and handles both redirection and parallel commands if necessary.
*/
void exec_command(char ** commands, int * checkpoints, int checkpoints_count){

    if(commands == NULL || checkpoints_count == -1){
        return;
    }

    // Each command has two checkpoints indicating the start/end indices of its tokens.
    size_t * pid = (size_t *) malloc(sizeof(size_t) * (checkpoints_count/2));

    // This variable will indicate the index of the first token in each command (start index).
    int checkpoint_index = 0;

    while(checkpoint_index < checkpoints_count){

        char * path;
        if((path = is_file_exist(commands[checkpoints[checkpoint_index]])) == NULL){
            display_error();
            free(path);
            free(pid);
            return;
        }

        int command_size = checkpoints[checkpoint_index+1] - checkpoints[checkpoint_index];
        char ** single_command = get_single_command(commands, checkpoints, checkpoint_index, command_size);
        
        int original_stdout;
        int original_stderr;

        int redirect_count = handle_redirection(single_command, command_size, checkpoint_index, &original_stdout, &original_stderr);

        if(redirect_count == -1){
            free_resources(single_command, path);
            free(pid);
            return;
        }

        exec_single_command(single_command, path, checkpoint_index, pid);

        if(redirect_count == 1){
            restore_stdout_stderr(original_stdout, original_stderr);
        }

        checkpoint_index+=2;
        free_resources(single_command, path);
    }

    wait_for_child_processes(pid, checkpoints_count);
    free(pid);
}

/**
 * Execute the single sparated command (subarray) from the parallel commands statement (&) if exited.
 * If there is no parallel commands, it also performs a single command execution.
*/
void exec_single_command(char ** single_command, char * path, int checkpoint_index, size_t * pid){

    pid[checkpoint_index/2] = fork();

    if(pid[checkpoint_index/2] == -1){
        exit(1);
    }else if(pid[checkpoint_index/2] == 0){

        execv(path, single_command);
        display_error();
        exit(1);
    }
}

/**
 * This function checks if there are any redirections (>) in the command and handles them.
 * On error it returns -1. If there is only one redirection, it handles it and returns 1.
 */
int handle_redirection(char **single_command, int command_size, int checkpoint_index, int * original_stdout, int * original_stderr){
    int redirect_count = 0;
    if((redirect_count = redirect_check(single_command, command_size)) == -1){
        return -1;
    }else if(redirect_count == 1){

        *original_stdout = dup(1);
        *original_stderr = dup(2);

        if(redirect_stdout_stderr(single_command[command_size]) == -1){
            display_error();
            return -1;
        }
        single_command[command_size] = NULL;
        single_command[command_size-1] = NULL;
    }

    return redirect_count;
}

/**
 * This function copies the subarray of the parallel commands and separate them
 * into single command array each itteration to be executed in the background.
*/
char ** get_single_command(char **commands, int *checkpoints, int checkpoint_index, int command_size){

    char **single_command = (char **)malloc(sizeof(char *) * (command_size + 2));
    if (single_command == NULL) {
        return NULL;
    }

    size_t i;
    for (i = checkpoints[checkpoint_index]; i <= checkpoints[checkpoint_index + 1]; i++) {
        single_command[i - checkpoints[checkpoint_index]] = commands[i];
    }

    single_command[i - checkpoints[checkpoint_index]] = '\0';

    return single_command;
}

void free_resources(char **single_command, char *path){
    free(single_command);
    free(path);
}

void wait_for_child_processes(size_t * pid, int checkpoints_count){
    for (size_t i = 0; i < checkpoints_count / 2; i++) {
        waitpid(pid[i], NULL, 0);
    }
}


/**
 * This function takes in a list of strings, which represent the commands that the user entered, and an integer, 
 * which represents the number of elements in the checkpoints list.
 * It then goes through the commands and finds the start/end indices of parallel commands.
 * If there are any consecutive duplicates '&' operators, it returns -1.
 */
int get_command_checkpoints(char ** commands, int token_count, int * checkpoints){

    int checkpoint_index = 0;
    int f = 0;
    for (size_t i = 0; i < token_count; i++)
    {
        if((strcmp(commands[i], "&") == 0 && i!= token_count -1 && strcmp(commands[i], commands[i+1]) == 0) || strcmp(commands[0], "&") == 0){
            return -1;
        }
        else if(strcmp(commands[i], "&") == 0){
            checkpoints[checkpoint_index++] = i - 1;
            f = 0;
            continue;
        }
        else if(f == 0){
            checkpoints[checkpoint_index++] = i;
            f = 1;
        }
    }

    if(strcmp(commands[token_count - 1], "&") != 0){
        checkpoints[checkpoint_index++] = token_count - 1;
    }

    return checkpoint_index;
}

/**
 * This function takes in a list of strings, which represent the command that the user entered, and the size of the command.
 * It then checks if there are any redirections in the command, and if there are, it returns 1.
 * If there is more than one or no file name after >, it returns -1.
 */
int redirect_check(char ** single_command, int command_size){

    int redirect_count = 0;

    for (size_t i = 0; i <= command_size; i++)
    {
        if(strcmp(single_command[i], ">") == 0 && (i != command_size-1)){
            display_error();
            return -1;
        }
        else if(strcmp(single_command[i], ">") == 0){
            redirect_count++;
        } 
    }

    if(redirect_count > 1){
        display_error();
        return -1;
    }

    return redirect_count;

}