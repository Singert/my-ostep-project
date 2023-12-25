#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char * argv[]){


    // Checking correct number of arguments
    if( argc < 2){
        exit(0);
    }

    for (int i = 1; i < argc; i++)
    {
        // Opening file in read mode
        FILE *fd = fopen(argv[i], "r");

        if (fd == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        // Buffer with pre-defined size to receive from the file stream (fd)
        char buffer[100];

        // Reading from file until it ends (line by line)
        while( fgets(buffer, sizeof(buffer), fd) !=NULL ) {   
            printf("%s", buffer);
        }

        fclose(fd);
    }
    
   
    
    return 0;
}
