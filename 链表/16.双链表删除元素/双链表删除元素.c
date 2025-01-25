#include <stdio.h>
#include <stdlib.h>

typedef struct Node {

    int x; // 数据
    struct Node *prev; // 前驱指针
    struct Node *next; // 后继指针
} Node;

void remove_element(Node *node)
{
    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }
    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }

    free(node);
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

    remove_element(tail->next); // 移除第二个节点

    Node *temp = tail->next;
    remove_element(tail); // 移除尾节点
    tail = temp; // 更新尾节点

    for (Node *curr = tail; curr != NULL; curr = curr->next)
    {
        printf("%d ", curr->x);
    }
}