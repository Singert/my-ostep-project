#include "wish.h"

void shell_start(char * batchfile){

    FILE * fp;
    int w = 0;

    if(strcmp(batchfile, "stdin") == 0){
        fp = stdin;
        w  = 1;
    }else{
        fp = fopen(batchfile, "r");
        if(fp == NULL){
            fprintf(stderr, "%s", error_message);
            exit(1);
        }
    }

    while(1){
        char ** arg_tokens = tokenize(fp, w);
        arg_tokens = arg_tokens;    // To avoid warnings about unused variables
    }

}



char ** tokenize(FILE * stream, int input_type){

    char * cmd_tokens = NULL;
    int char_count = 0;

    if((char_count = read_line(&cmd_tokens, stream)) == EOF){
        exit(0);
    }

    int token_count = count_tokens(cmd_tokens, char_count);
    char ** arg_tokens;

    if(token_count){
        arg_tokens = (char **) malloc(sizeof(char *) * (token_count +1));

        token_extract(cmd_tokens, arg_tokens, " \n");

        command_select(arg_tokens, token_count);
    }

    if(input_type){
        printf("wish> ");
    }

    return arg_tokens;
}

void command_select(char ** commands, int token_count){

    if(strcmp(commands[0], "exit") == 0 && token_count == 1){
        exit(0);

    }else if(strcmp(commands[0], "cd") == 0){

        if(token_count != 2 || chdir(commands[1]) == -1){
            fprintf(stderr, "%s", error_message);
            exit(0);
        }

    }else if(strcmp(commands[0], "path") == 0){
        
        path_init(commands, token_count);

    }else{
        int checkpoints[100] = {0};
        int checkpoints_count = tokenize_commands(commands, token_count, checkpoints);
        exec_cmd(commands, checkpoints, checkpoints_count);
    }
}

int redirect_check(char ** single_command, int command_size){

    int redirect_count = 0;

    for (size_t i = 0; i <= command_size; i++)
    {
        if(strcmp(single_command[i], ">") == 0 && (i != command_size-1)){
            fprintf(stderr, "%s", error_message);
            return -1;
        }

        if(strcmp(single_command[i], ">") == 0){
            redirect_count++;
        }
        
    }

    if(redirect_count > 1){
        fprintf(stderr, "%s", error_message);
        return -1;
    }

    return redirect_count;

}

int redirect_start(char * filename){

    int fd = open(filename, O_WRONLY|O_TRUNC|O_CREAT, 0644);

    if (fd < 0) {
        fprintf(stderr, "%s", error_message);
        return -1;
    }

    if (dup2(fd, 1) < 0){
        fprintf(stderr, "%s", error_message);
        return -1; 
    }

    if (dup2(fd, 2) < 0){
        fprintf(stderr, "%s", error_message);
        return -1; 
    }

    close(fd);
    return 0;
}

void redirect_end(int original_stdout, int original_stderr){
    
    if(dup2(original_stdout, 1) < 0){
        fprintf(stderr, "%s", error_message);
        return; 
    }

    if(dup2(original_stderr, 2) < 0){
        fprintf(stderr, "%s", error_message);
        return; 
    }

    close(original_stdout);
    close(original_stderr);
}

int tokenize_commands(char ** commands, int token_count, int * checkpoints){
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

void path_init(char ** commands, int token_count){
    int j = 0;
    while(j < token_count){
        env[j] = NULL;
        j++;
    }


    int i = 1;
    while(i < token_count){

        env[i-1] = commands[i];
        i++;
    }
}


void exec_cmd(char ** commands, int * checkpoints, int checkpoints_count){

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
            fprintf(stderr, "%s", error_message);
            return;
        }

        int command_size = checkpoints[j+1] - checkpoints[j];
        char ** single_command = (char **) malloc(sizeof(char *) * (command_size + 2));


        for (size_t i = checkpoints[j]; i <= checkpoints[j+1]; i++)
        {
            single_command[i-checkpoints[j]] = commands[i];
        }
        
        int redirect_count = 0;

        if((redirect_count = redirect_check(single_command, command_size)) == -1){
            return;

        }else if(redirect_count == 1){

            original_stdout = dup(1);
            original_stderr = dup(2);

            if(redirect_start(commands[checkpoints[j+1]]) == -1){
                fprintf(stderr, "%s", error_message);
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
            fprintf(stderr, "%s", error_message);
            exit(1);

        }

        if(redirect_count == 1){
            redirect_end(original_stdout, original_stderr);
        }

        j+=2;
    }

    for (size_t i = 0; i < checkpoints_count/2; i++)
    {
        waitpid(pid[i], NULL, 0);
    }
    
    
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


int read_line(char ** buffer, FILE * stream){
    size_t len = 0;
    int read = 0;

    read = getline(buffer, &len, stream);

    return read;

}

int count_tokens(char * tokens, int char_count){
    int token_count = 0;
    char last_char = 0;
    for (size_t i = 0; i < char_count; i++)
    {
        if((tokens[i] == ' ' || tokens[i] == '\n') && (last_char != 0 && last_char != ' ')){
            token_count++;
        }else if((tokens[i] == '>' || tokens[i] == '&') && i != 0 && i != char_count -2 && tokens[i-1] != ' ' && tokens[i+1] != ' '){
            token_count+=2;
        }else if((tokens[i] == '>' || tokens[i] == '&') && ((last_char == ' ' && tokens[i+1] != ' ' && i != char_count -2) || (last_char != ' ')) && i != 0){
            token_count++;
        }
        last_char = tokens[i];
    }

    return token_count;
}


void token_extract(char * source, char ** destination, char * delim){
    int i = 0;
    char * temp;
    char * trim_res;

    while((temp = strsep(&source, delim))){
        if(*temp){
            int j;
            int last = 0;
            for (j = 0; temp[j] != '\0' ; j++){
                
                if(temp[j] == '>' || temp[j] == '&'){
                    
                    if((trim_res = token_trim(temp, last, j-1)) != NULL){
                        destination[i] = trim_res;
                        i++;
                    }

                    destination[i] = (temp[j] == '>' ? ">" : "&");
                    i++;

                    last = j+1;

                }
            }
            
            if((trim_res = token_trim(temp, last, j-1)) != NULL){
                destination[i] = trim_res;
                i++;
            }
        }
    }

}

char * token_trim(char * token, int start, int end){
    if(end >= start){
        char * result = malloc(sizeof(char) * (end - start + 1));

        for (int i = start; i <= end; i++){
            result[i-start] = token[i];
        }

        return result;
    }else{
        return NULL;
    }
    
}