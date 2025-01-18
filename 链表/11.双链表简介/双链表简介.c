#include <stdio.h>
#include <stdlib.h>

typedef struct Node {

    int x; // 数据
    struct Node *prev; // 前驱指针
    struct Node *next; // 后继指针
} Node;

int main(int argc, const char * argv[]) {

    Node *tail = malloc(sizeof(Node)); // 创建尾节点

    if (tail == NULL) // 如果内存分配失败
    {
        return 1;
    }
    tail->x = 1;

    tail->prev = NULL; // 前驱指针指向NULL
    tail->next = malloc(sizeof(Node)); // 创建下一个节点
    if (tail->next == NULL)
    {
        return 1;
    }
    tail->next->x = 2;

    tail->next->prev = tail;
    tail->next->next = malloc(sizeof(Node));
    if (tail->next->next == NULL)
    {
        return 1;
    }
    tail->next->next->x = 7;
    tail->next->next->prev = tail->next;
    tail->next->next->next = NULL;

    Node *head = tail->next->next; // 头节点
}