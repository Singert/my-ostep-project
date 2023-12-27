#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>

void shell_start(char * batchfile);

int count_tokens(char * tokens, int char_count);

int read_line(char ** buffer, FILE * stream);

char ** tokenize(FILE * stream, int input_type);

void token_extract(char * source, char ** destination);

void exec_cmd(char ** commands);

void command_select(char ** commands, int token_count);

char * is_file_exist(char * path);

void path_init(char ** commands, int token_count);

char * error_message = "An error has occurred\n";

char * env[500];

int main(int argc, char * argv[]){

    // argc = 2;
    // argv[0] = "./wishhh";
    // argv[1] = "test.txt";


    env[0] = "/bin";
    env[1] = NULL;


    if(argc > 2){   
        fprintf(stderr, "%s", error_message);
        exit(1);
    }else if(argc == 2){
        shell_start(argv[1]);
        exit(0);
    }else if(argc == 1){
        printf("wish> ");
        shell_start("stdin");
    }

    return 0;
}

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
        arg_tokens = arg_tokens;
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
        arg_tokens = (char **) malloc(sizeof(char *) * token_count +1);

        token_extract(cmd_tokens, arg_tokens);

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
            exit(1);
        }

    }else if(strcmp(commands[0], "path") == 0){
        
        path_init(commands, token_count);

    }else{
        exec_cmd(commands);
    }
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


void exec_cmd(char ** commands){

    if(commands == NULL){
        return;
    }

    char * path;
    if((path = is_file_exist(commands[0])) == NULL){
        fprintf(stderr, "%s", error_message);
        return;
    }

    size_t pid = fork();

    if(pid == -1){
        exit(1);
    }else if(pid == 0){

        execvp(path, commands);
        fprintf(stderr, "%s", error_message);
        exit(1);

    }else{
        size_t ws = wait(NULL);
        if(ws == -1){
            exit(1);
        }
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
        if((tokens[i] == ' ' && (last_char != 0 && last_char != ' ')) || (tokens[i] == '\n' && (last_char != 0 && last_char != ' '))){
            token_count++;
        }
        last_char = tokens[i];
    }

    return token_count;
}


void token_extract(char * source, char ** destination){
    int i = 0;
    char * temp;
    while((temp = strsep(&source, " \n"))){
        if(*temp){
            destination[i] = temp;
            i++;
        }
    }
}