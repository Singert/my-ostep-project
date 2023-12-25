#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){


    // Checking correct number of arguments
    if( argc < 2){
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for(int i = 1; i < argc; i ++){

        FILE *fd = fopen(argv[i], "r");

        if (fd == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }
        
        while(1){
            int r = 0;
            
            if(fread(&r, 4, 1, fd) == 0){
                break;
            }

            char r_char;

            if(fread(&r_char, 1, 1, fd) == 0){
                break;
            }

            for (size_t j = 0; j < r; j++)
            {
                fputc(r_char, stdout);
            }
            
        }
    }
    
    
    return 0;
}