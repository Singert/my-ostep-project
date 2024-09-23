# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# define BUFFER_SIZE 1024
//parse commands

int main(int argc, char* argv[])
{

    for (int i = 1; i < argc; i++)
    {
        if (argv[i] != NULL)
        {
            printf("filename : %s\n",argv[i]);
            FILE *fp = fopen(argv[i],"r");
            if (fp == NULL)
            {
                fprintf(stderr,"failed to open file\n");
                if (i == argc -1)
                {
                    exit(1);
                }
                else{continue;}
            }
            char buffer[BUFFER_SIZE];
            while(fgets(buffer,BUFFER_SIZE,fp)!=NULL)
            {
                printf("%s",buffer);
            }
            fclose(fp);
        }
    }
    return 0;
}