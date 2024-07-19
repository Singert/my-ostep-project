#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void outsd (char* line[] , int linecount){
    for ( int i = linecount-1 ; i >= 0 ; i--)
    {
        printf("%s", line[i]);
        // Free the allocated memory for the line buffer
        free(line[i]);
    }
}

char* strfile(char **string)
{
    char delim[20] = "/"; 
    char* o_Ptr;
    char* out_ptr;  
    while ((o_Ptr = strsep(string, delim)) != NULL){ 
        out_ptr = o_Ptr ;
    }
    return out_ptr;
}

int main(int argc, char *argv[]) {

    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
   size_t len = 0;
   ssize_t read;
   int lineCount = 1;
   int character;
   
   if(argc == 1){
        char *line[5] = {NULL};
        // Read the file line by line and print each line
        lineCount = 0;
        while ((read = getline(&line[lineCount], &len, stdin)) != EOF) {
            lineCount++;
        }
        outsd(line , lineCount);
   }
   else
   {
        // Open the file for reading
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n",argv[1]);
            exit(1);
        }
        while ((character = getc(fp)) != EOF) { // Read characters using getc()
            if (character == '\n') {
                lineCount++;
            }    
        }
        char *line[lineCount] = {NULL};
        fclose(fp);
        
        FILE *inputFile = fopen(argv[1], "r"); // Open input file using fopen()
        if (inputFile == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n",argv[1]);
            exit(1);
        }
        int lineNum = 0;
        // Read the file line by line and print each line
        while ((read = getline(&line[lineNum], &len, inputFile)) != -1) {
            lineNum++;
        }
        fclose(inputFile);// Close the file  
   
        if (argc == 3)
        {
            FILE *outputFile = fopen(argv[2], "w"); // Open output file using fopen()
            if ((strcmp(argv[1],argv[2])) == 0 || strcmp ( strfile(&argv[1]) , strfile(&argv[2]) ) == 0 )
            {
                fprintf(stderr, "reverse: input and output file must differ\n");
                exit(1);
            }
            if (outputFile == NULL) {
                fprintf(stderr, "reverse: cannot open file '%s'\n",argv[2]);
                exit(1);
            }
            for ( int i = lineCount-1 ; i >= 0 ; i--)
            {
                fprintf(outputFile, "%s" ,line[i]);
            }
            fclose(outputFile);
        }
        else if (argc == 2)
        {
            outsd(line , lineCount);
        }
    }
   return 0;
}