#include <stdio.h>
#include <stdlib.h>

typedef struct Node {

    int x; // 数据
    struct Node *prev; // 前驱指针
    struct Node *next; // 后继指针
} Node;

void insert_end(Node **head, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        exit(1);
    }
    new_node->x = value; // 新节点的值

    new_node->next = NULL; // 新节点的下一个节点为 NULL
    new_node->prev = *head; // 插入到链表的末尾

    (*head)->next = new_node; // 原来的尾节点的下一个节点为新节点
    *head = new_node; // 新节点变成新的尾节点
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

    insert_end(&head, 2);
    insert_end(&head, 3);
    insert_end(&head, 4);


    for (Node *curr = tail; curr != NULL; curr = curr->next)
    {
        printf("%d ", curr->x);
    }
}