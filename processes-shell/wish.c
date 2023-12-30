#include "wish.h"

char * error_message = "An error has occurred\n";

char * env[500];
int env_count = 1;

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