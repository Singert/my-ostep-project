#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){


    // Checking correct number of arguments
    if( argc < 2){
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }


    char cur_char = 0;
    char last_char = 0;
    int count = 1;

    for (int i = 1; i < argc; i++)
    {
        FILE *fd = fopen(argv[i], "r");

        if (fd == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while((cur_char = fgetc(fd)) != EOF){

            // Evaluates to true for the first itteration only
            if(last_char == 0){
                last_char = cur_char;

            }else if(cur_char == last_char){
                count++;
            }else{
                

                fwrite(&count, 4, 1, stdout);
                fputc(last_char, stdout);

                last_char = cur_char;
                count = 1;
            }
            
        }

    }

    // Cover the last edge case
    fwrite(&count, 4, 1, stdout);
    fputc(last_char, stdout);

    
    
    
   
    
    return 0;
}