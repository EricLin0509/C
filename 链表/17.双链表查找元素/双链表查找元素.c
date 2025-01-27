#include <stdio.h>
#include <stdlib.h>

typedef struct Node {

    int x; // 数据
    struct Node *prev; // 前驱指针
    struct Node *next; // 后继指针
} Node;

Node *find_element(Node *tail, int value)
{
    for (Node *curr = tail; curr != NULL; curr = curr->next)
    {
        if (curr->x == value)
        {
            return curr;
        }
    }
    return NULL; // 没找到的情况
}

Node *find_element_recursive(Node *node ,int value)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->x == value)
    {
        return node;
    }

    return find_element_recursive(node->next, value);   
}

void insert_begining(Node **tail, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        exit(1);
    }

    new_node->x = value; // 新节点的值
    new_node->prev = NULL; // 新节点的前一个节点为 NULL
    new_node->next = *tail; // 插入到链表的开头
    if (*tail != NULL) 
    {
        (*tail)->prev = new_node; // 新节点的下一个节点为原来的尾节点
    }
    *tail = new_node; // 新节点变成新的尾节点
}

void init(Node **tail, Node **head, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }

    new_node->x = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    *tail = new_node; // 尾节点为新节点
    *head = new_node; // 头节点为新节点
}

int main(int argc, const char * argv[]) {

    Node *tail = NULL;
    Node *head = NULL;
    
    init(&tail, &head, 1);
    insert_begining(&tail, 2);
    insert_begining(&tail, 3);
    insert_begining(&tail, 4);

    Node *found = find_element(tail, 2);
    if (found != NULL)
    {
        printf("value: %d, next: %zu\n", found->x, found->next);
    }

    Node *found_recursive = find_element_recursive(tail, 1);
    if (found_recursive != NULL)
    {
        printf("value: %d, next: %zu\n", found_recursive->x, found_recursive->next);
    }
}