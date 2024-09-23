# include <stdio.h>
# include <stdlib.h>
#include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# define COUNT 1024
# define BUFFER_SIZE 1024
typedef struct lnode
{
    char* value;
    struct lnode* next;
}lnode;

typedef struct llist
{
    lnode* head;
}llist;

llist* create_list()
{
    llist* list =(llist*)malloc(sizeof(llist));
    list->head = NULL;
    return list;
}

void add_node(char*value,llist* list)
{
    lnode* curr = (lnode*)malloc(sizeof(lnode));
    curr->value = value;
    curr->next = list->head;
    list->head = curr;
}

void print_list(llist*list)
{
    lnode* curr = (lnode*)malloc(sizeof(lnode));
    curr = list->head;
    
}

//parse_command
void parse_command(int arg,char* args[],char* results[])
{
    if (arg <= 2)
    {
        perror("no enough arguments");
        exit(1);
    }
    else 
    {
        for(int i = 1; i < arg; i++)
        {
            strcpy(results[i-1],args[i]);
        }
    }
}

int main(int argc, char*argv[])
{
    llist* src = create_list();
    llist*dest = create_list();
    // czx,lpt.ltq,xww,fz,hcy,lmz,cys,scd,ryn,xlx,mjy,yzy（未回复），zjc，14个，tml，wbc（叫了没？）
//有没叫道的吗，老赵估计睡觉了
    char* cmd[COUNT];
    parse_command(argc, argv, cmd);
    int i = 1;
    ssize_t byteReads;
    
    while(cmd[i]!= NULL)
    {
        FILE* fp = fopen(cmd[i], "r");
        if (fp == NULL)
        {
            perror("failed to open file\n");
        }
        else   
        {
            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            while ((read = getline(&line, &len, fp)!= -1))
            {
                add_node(line, src);
            }
        }

    }

    lnode *curr = src->head;
    while (curr!= NULL)
    {
        if (strstr(curr->value,cmd[0])!= NULL)
        {
            add_node(curr->value, dest);
        }
        
        curr = curr->next;
    }
    print_list(dest);
    return 0;
}