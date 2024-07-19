#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


// The search function wgrep takes a pointer to a FILE type and the search word.
void wgrep(FILE * stream, char * srch_word){
    char *line = NULL;
    size_t len = 0;

    while(1){

        /*
        * The function getdelim is similar to fgets, but it differs in that it 
        * dynamically allocates memory for the input line and
        * automatically resizes the buffer to accommodate long lines.
        */
        
        size_t read = getdelim(&line, &len, '\n', stream);
        if (read != -1) {

            // The function strstr searches for str2 in str1
            char * res = strstr(line, srch_word);
            if(res == NULL){
                continue;
            }


            printf("%s", line);

        } else {
            break;
        }

    }
    
    free(line);
}



int main(int argc, char * argv[]){


    // If there is a search word without a filename, the standard input (stdin) is read from.
    if(argc == 2){

        wgrep(stdin, argv[1]);
        
    }
    // If both searcword and filename exists, search for this word in the file.
    else if(argc >= 3){

        for (int i = 2; i < argc; i++)
        {
            FILE *fd = fopen(argv[i], "r");

            if (fd == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }

            wgrep(fd, argv[1]);
        }
        
    }else{
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    return 0;
}