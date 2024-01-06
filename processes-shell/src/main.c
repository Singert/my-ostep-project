#include "../include/shell.h"

// ANSI escape codes for color formatting
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char * env[500];

int main(int argc, char * argv[]){

    if(argc > 2){   
        display_error();
        exit(1);
    }
    char * filename = (argc == 2) ? argv[1] : "stdin";
    FILE * input_file = shell_init(filename);
    while (1)
    {   
        if(input_file == stdin){
            printf(ANSI_COLOR_GREEN "wish> " ANSI_COLOR_RESET);
        }
        shell_start(input_file);
    }
    return 0;
}