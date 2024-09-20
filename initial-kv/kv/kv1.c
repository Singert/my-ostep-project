# include <stdio.h>
# include <string.h>
#include <time.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# define MAX_TOKENS 4 //the 4th str set NULL, as sign of command end;
# define BUFFER_SIZE 1024// the max size of buffer
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


//write list to file
void write_list(llist * list)
{
    int fd = open("./db",O_CREAT | O_WRONLY | O_TRUNC,S_IRWXU);
        l_node* curr = list->head;
    while(curr != NULL)
    {
        dprintf(fd,"%d,%s\n",curr->key,curr->value);
        curr = curr->next;
    }
}
//load data from db
// void load_list(llist* list)
// {
//     int fd = open("./db",O_RDONLY);
//     char buffer[BUFFER_SIZE];
//     ssize_t bytesRead;
//     int i = 0;
//     // while((bytesRead = read(fd,&buffer[i],BUFFER_SIZE-i-1))>0)
//     // {   
//     //     printf("i:%d\n",i);
//     //     for (int j = i; j <i+bytesRead; j++)
//     //     {   
//     //         printf("Butter : %s\n",buffer);
//     //         if (buffer[j] == '\n')
//     //         { 
//     //             printf("j:%d\n",j);
//     //             buffer[j + 1] = '\0';
//     //             char* token_k = strtok(buffer, ",");
//     //             char* token_v = strtok(NULL, "\0");
//     //             add(atoi(token_k),token_v,list);
//     //             i = 0;
//     //             break;
//     //         }
//     //                     // 如果到了缓冲区的末尾，且没有换行符
//     //         if (j == BUFFER_SIZE - 1) {
//     //             buffer[BUFFER_SIZE - 1] = '\0'; // 确保字符串结束
//     //             printf("%s", buffer); // 打印当前缓冲区内容
//     //             i = 0; // 清空缓冲区
//     //         } else {
//     //             i++;
//     //         }
//     //     }
//     // }
//     while((bytesRead = read(fd, &buffer[i], BUFFER_SIZE - i - 1)) > 0)
//     {   
//         buffer[bytesRead + i] = '\0';  // 确保字符串结束
//         char *line = strtok(buffer, "\n");  // 按行分割
//         while (line != NULL)
//         {
//             char *token_k = strtok(line, ",");
//             char *token_v = strtok(NULL, ",");
//             if (token_k != NULL && token_v != NULL)
//             {
//                 add(atoi(token_k), token_v, list);  // 将key-value对加入链表
//             }
//             line = strtok(NULL, "\n");
//         }
//         i = 0;  // 重置缓冲区索引
//     }
// }
// void load_list(llist* list)
// {
//     int fd = open("./db", O_RDONLY);
//     if (fd < 0) {
//         printf("Failed to open file\n");
//         return;
//     }

//     char buffer[BUFFER_SIZE];
//     ssize_t bytesRead;
//     int i = 0;
    
//     while ((bytesRead = read(fd, &buffer[i], BUFFER_SIZE - i - 1)) > 0) {
//         buffer[bytesRead + i] = '\0';  // 确保字符串结束
        
//         char *line = strtok(buffer, "\n");  // 按行分割
        
//         while (line != NULL) {
//             char *token_k = strtok(line, ",");   // 分割出 key
//             char *token_v = strtok(NULL, ",");   // 分割出 value
            
//             if (token_k != NULL && token_v != NULL) {
//                 add(atoi(token_k), strdup(token_v), list);  // 将 key 和 value 加入链表
//             }
            
//             line = strtok(NULL, "\n");  // 读取下一行
//         }
        
//         i = 0;  // 重置缓冲区索引
//     }
    
//     close(fd);  // 关闭文件
// }
// void load_list(llist* list)
// {
//     int fd = open("./db", O_RDONLY);
//     if (fd < 0) {
//         perror("Failed to open db file");
//         return;
//     }

//     char buffer[BUFFER_SIZE];
//     ssize_t bytesRead;
//     char *line;
//     while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
//         buffer[bytesRead] = '\0';  // 确保字符串结束
//         line = strtok(buffer, "\n");  // 按行分割

//         while (line != NULL) {
//             int key;
//             char value[BUFFER_SIZE];  // 使用足够大的缓冲区
//             if (sscanf(line, "%d,%s", &key, value) == 2) {
//                 // 成功解析key和value
//                 add(key, strdup(value), list);  // 添加到链表
//             }
//             line = strtok(NULL, "\n");  // 读取下一行
//         }
//     }
//     close(fd);
// }

void load_list(llist* list)
{
    int fd = open("./db", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open db file");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    int key;
    char value[BUFFER_SIZE];

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytesRead] = '\0';  // 确保字符串结束
        char *line = strtok(buffer, "\n");  // 按行分割

        while (line != NULL) {
            if (sscanf(line, "%d,%s", &key, value) == 2) {
                // 成功解析key和value
                add(key, strdup(value), list);  // 添加到链表
            }
            line = strtok(NULL, "\n");  // 读取下一行
        }
    }
    close(fd);
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
    load_list(list);
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
    write_list(list);

    return 0;
}