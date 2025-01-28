#include <stdio.h>
#include <stdlib.h>

typedef struct Node {

    int x; // 数据
    struct Node *prev; // 前驱指针
    struct Node *next; // 后继指针
} Node;

void revserse(Node **tail, Node **head)
{
    Node *curr = *tail; // 从尾节点开始遍历
    
    while (curr!= NULL)
    {
        Node *next = curr->next; // 保存当前节点的下一个节点

        curr->next = curr->prev; // 把当前节点的 next 指向 prev
        curr->prev = next; // 把 prev 指向当前节点

        curr = next; // 把当前节点指向 next
    }

    Node *temp = *tail; // 使用一个临时变量保存 tail
    *tail = *head; // 把 tail 指向 head
    *head = temp; // 把 head 指向 temp
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

    for (Node *curr = head; curr != NULL; curr = curr->prev)
    {
        printf("%d ", curr->x);
    }
    printf("\n");

    revserse(&tail, &head);

    for (Node *curr = head; curr!= NULL; curr = curr->prev)
    {
        printf("%d ", curr->x);
    }
}