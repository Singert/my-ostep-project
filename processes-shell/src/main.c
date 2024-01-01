#include "../include/shell.h"

char * env[500];

int main(int argc, char * argv[]){

    if(argc > 2){   
        display_error();
        exit(1);
    }

    char * filename = (argc == 2) ? argv[1] : "stdin";
    FILE * input_file = shell_init(filename);

    initialize_path();

    while (1)
    {   
        if(input_file == stdin){
            printf("wish> ");
        }
        
        shell_start(input_file);
    }
    
    return 0;
}