#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exec_batch(char * batchfile);


int count_tokens(char * tokens, int char_count);

int read_line(char ** buffer, FILE * stream);


int main(int argc, char * argv[]){

    argc = 2;
    argv[0] = "./wishhh";
    argv[1] = "test.txt";

    char * error_message = "An error has occurred\n";

    if(argc > 2){
        fprintf(stderr, "%s", error_message);
        exit(1);
    }else if(argc == 2){
        exec_batch(argv[1]);
        exit(0);
    }

    while (1)
    {
        printf("whish> ");

        char * buffer = NULL;
        if(read_line(&buffer, stdin) != -1){
            if(strcmp(buffer, "exit\n") == 0){
                exit(0);
            }
        }
        
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

void exec_batch(char * batchfile){
    FILE * fp = fopen(batchfile, "r");

    if(fp == NULL){
        fprintf(stderr, "Could not open file %s\n", batchfile);
        exit(1);
    }

    char * cmd_tokens = NULL;

    int char_count = 0;

    while((char_count = read_line(&cmd_tokens, fp)) != EOF){

        int token_count = count_tokens(cmd_tokens, char_count);


        char ** arg_tokens = (char **) malloc(sizeof(char *) * token_count +1);
        int i = 0;

        while((arg_tokens[i] = strsep(&cmd_tokens, " "))){
            i++;

        }


        
        

    }

}