//The code only implements few functionalities that 
// parses instructions input 
//and maintains a linked list while performs basic opreations.

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# define MAX_TOKENS 4 //the 4th str set NULL, as sign of command end;

typedef struct l_node
{
    int key;
    char*value;
    struct l_node*next;
} l_node;

typedef struct
{
    struct l_node *head;
    // l_node *tail;
} llist;

llist* create()
{
    llist *linklist = (llist*)calloc(1,sizeof(llist));
    (*linklist).head =NULL;
    return linklist;
}

void add(int k,char *v,llist* list)
{
    l_node *node = (l_node*)malloc(sizeof(l_node));
    node->key = k;
    node->value = v;
    node->next = list->head;
    list->head = node;    
}
l_node* nodesearch(int k,llist *list)
{
    l_node *curr = list->head;
    while (curr != NULL)
    {
        if (curr->key == k)
        {
            break;
        }
        else 
        {
            curr = curr->next;
        }
    }
    return curr;
}//do not check if return is null;

char* value_search(int k,llist* list)
{
    l_node *curr = nodesearch(k, list);
    if (curr)
    {
        return curr->value;
    }
    else 
    {
        return NULL;
    }
}

int del_node(int k,llist* list)
{
    l_node *curr = list->head;
    if (curr->key == k)
    {
        curr = curr->next;
        return 1;
    }
    while (curr->next != NULL)
    {
        if (curr->next->key == k)
        {
            curr->next = curr->next->next;
            return 1;
        }
        else 
        {
            curr = curr->next;
        }
    }
    return 0;
}

void clear_list(llist* list)
{
    list->head = NULL;
}

void print_list(llist* list)
{
    l_node* curr = list->head;
    while(curr != NULL)
    {
        printf("key: %d, value: %s\n",curr->key,curr->value);
        curr = curr->next;
    }
    printf("that's all\n");
}


//parse command,
//return an array of str which stores parsed commands;    
char** parse_command(char*command)
{
    char **result = (char**)malloc(MAX_TOKENS * sizeof(char*));
    if (command == NULL)
    {
        return NULL;
    }
    else
    {
        int i = 0;
        char *token = strtok(command, ",");
        while (token != NULL && i < MAX_TOKENS)
        {
            result[i]= token;
            i++;
            token = strtok(NULL, ",");
        }
        result[i] = NULL;
        return result;
    }
    
}


int main(int argc, char* argv[])
{   
    printf("test0\n");
    // linked list initial
    printf("argc : %d\n",argc);
    for (int i = 0;i<= argc; i++)
    {
        printf("argv[%d] is %s\n",i,argv[i]);
    }
    llist * list = create();
    // parse instruction
    if (argc < 1)
    {
        printf("instruction parse failed.\n");
        exit(1);
    }
    int i = 1;
    while (i < argc)
    {
        printf("current i = %d\n",i);
        // call function prase_command()
        char **cmd = parse_command(argv[i]);
        if (cmd == NULL)
        {
            printf("failed to parse current instruction : %s \n",argv[i]);
        }
        else 
        {
        // parse "put "
        // assume all key is non-negitive-number
            if (strcmp(cmd[0],"p") == 0)
            {
                printf("test P\n");
                if (cmd[1]!=NULL && cmd[2]!= NULL)
                {
                    add(atoi(cmd[1]),cmd[2],list);
                    printf("put success\n");
                }
                else{printf("no enough arguments to acomplish put\n");}
            } 
            //parse 'get'
            else if(strcmp(cmd[0],"g")==0)
                {
                printf("test G\n");
                if (cmd[1]!= NULL)
                {
                    char *result = value_search(atoi(cmd[1]), list);
                    if (result != NULL)
                    {
                        printf("the value of %d is %s\n",atoi(cmd[1]),result);
                    }
                }
                else{printf("no enough arguments to acomplish put\n");}
            }
            //parse 'delete'
            else if(strcmp(cmd[0],"d")==0)
            {
                printf("test D\n");
                if (cmd[1]!= NULL)
                {
                    int result = del_node(atoi(cmd[1]), list);
                    if (result)
                    {
                        printf("delete success\n");
                    }
                    else 
                    {
                        printf("delete failed\n");
                    }
                }
            }
            // parse "all"
            else if(strcmp(cmd[0],"a")==0)
            {
                printf("test A\n");
                print_list(list);
            }
            else if(strcmp(cmd[0], "c")==0)
            {
                printf("test C\n");
                clear_list(list);
            }
        }
    i++;
    }
    

    return 0;
}