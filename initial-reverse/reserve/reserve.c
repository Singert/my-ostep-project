//learn :字符串字面量的大小不等于字符串在内存中所占用的大小
// 同时 char* argv[]在内存的堆区中声明了一个指向字符串的指针所构成的数组，通常该数组的

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>

# define MAX_STRINGS 512
# define BUFFER_SIZE 2048

typedef struct lnode
{
    char* string;
    struct lnode * next;
} lnode;

typedef struct llist
{
    lnode* head;
}llist;

llist* create_list()
{
    llist* list = (llist*)malloc(sizeof(llist));
    list->head = NULL;
    return list;
}

void add_node(char* string,llist* list)
{
    lnode * curr = (lnode*)malloc(sizeof(lnode));
    curr->string = string;
    curr->next = list->head;
    list->head = curr;
}

void reserve(char * out_name,llist *list)
{
    int fd = open(out_name,O_CREAT | O_WRONLY | O_TRUNC,S_IRWXU);
    lnode * curr = list->head;
    while (curr != NULL)
    {
        dprintf(fd,"%s\n",curr->string);
        curr = curr->next;
    }
    close(fd);
}

int load_list(char * in_name,llist *list)
{
    printf("test Load\n");
    int fd = open(in_name,O_RDONLY);
    if (fd < 0)
    {
        perror("failed to open input");
        return -1;
    }
    ssize_t bytes_read;
    char  buffer[BUFFER_SIZE];
    char string[MAX_STRINGS];
    while((bytes_read=read(fd,buffer,BUFFER_SIZE-1))>0)
    {
        buffer[bytes_read] = '\0';
        char *line = strtok(buffer,"\n");
        while (line != NULL)
        {
            add_node(strdup(line),list);
            line = strtok(NULL,"\n");
        }
    }
    close(fd);
    return 1;
}

void parse(int arg,char* args[],char*result[],int* res)
{

    printf("test parse0\n");
    if (arg < 2)
    {
        result = NULL;
        *res = -1;
    }
    else if (arg == 2)
    {
        strcpy(result[0],"./");
        strcat(result[0], args[1]);
        result[1] = "./output";
        *res = 1;
    }
    else if (arg == 3)
    {
        printf("test parse1\n");
        strcpy(result[0],"./");
        strcat(result[0], args[1]);
        printf("test parse2\n");
        strcpy(result[1],"./");
        strcat(result[1], args[2]);
        printf("test parse3\n");
        *res = 1;
    }
    else 
    {
        result = NULL;
        *res = 0;
    }
}


int main(int argc, char*argv[])
{
    printf("argc ;%d\n",argc);
    int res;
    char* result[2];
    result[0] = malloc(8*sizeof(char));
    result[1] = malloc(9*sizeof(char));
    printf("test A\n");
    printf("test B\n");
    parse(argc, argv, result, &res);
    llist *list = create_list();
    load_list(result[0], list);
    printf("C\n");
    lnode* curr = list->head;
    while (curr != NULL)
    {
        printf("curr : %s\n",curr->string);
        curr=curr->next;
    }
    reserve(result[1], list);

    return 0;    
}