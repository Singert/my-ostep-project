#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exec_command(char * batchfile);

int count_tokens(char * tokens, int char_count);

int read_line(char ** buffer, FILE * stream);

char ** tokenize(FILE * stream, int input_type);


int main(int argc, char * argv[]){

    // argc = 2;
    // argv[0] = "./wishhh";
    // argv[1] = "test.txt";

    char * error_message = "An error has occurred\n";

    if(argc > 2){   
        fprintf(stderr, "%s", error_message);
        exit(1);
    }else if(argc == 2){
        exec_command(argv[1]);
        exit(0);
    }else if(argc == 1){
        printf("wish> ");
        exec_command("stdin");
    }

    return 0;
}




int read_line(char ** buffer, FILE * stream){
    size_t len = 0;
    int read = 0;

    read = getline(buffer, &len, stream);

    return read;

}

int count_tokens(char * tokens, int char_count){
    int token_count = 0;
    for (size_t i = 0; i < char_count; i++)
    {
        if(tokens[i] == ' ' || tokens[i] == '\n'){
            token_count++;
        }
    }

        return token_count;
}

char ** tokenize(FILE * stream, int input_type){

    char * cmd_tokens = NULL;
    int char_count = 0;

    if((char_count = read_line(&cmd_tokens, stream)) == EOF){
        exit(0);
    }

    if(strcmp(cmd_tokens, "exit\n") == 0){
        exit(0);
    }

    if(input_type){
        printf("wish> ");
    }

    int token_count = count_tokens(cmd_tokens, char_count);


    char ** arg_tokens = (char **) malloc(sizeof(char *) * token_count +1);
    int i = 0;

    while((arg_tokens[i] = strsep(&cmd_tokens, " "))){
        i++;
    }   

    return arg_tokens;
}

void exec_command(char * batchfile){

    FILE * fp;
    int w = 0;

    if(strcmp(batchfile, "stdin") == 0){
        fp = stdin;
        w  = 1;
    }else{
        fp = fopen(batchfile, "r");
        if(fp == NULL){
            fprintf(stderr, "Could not open file %s\n", batchfile);
            exit(1);
        }
    }

    
    while(1){

        char ** arg_tokens = tokenize(fp, w);

        
    }

}