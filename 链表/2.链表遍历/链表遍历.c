#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

int main(int argc, const char * argv[]) {

    Node root; //头节点
    root.x = 1;
    root.next = malloc(sizeof(Node));
    root.next->x = 2;
    root.next->next = malloc(sizeof(Node));
    root.next->next->x = 3;
    root.next->next->next = NULL;
    // 共有三个节点

    Node *curr = &root; //初始化当前节点为头节点

    // 使用while循环
    while(curr != NULL)
    {
        printf("%d\n",curr->x); // 输出当前节点的值
        curr = curr->next; // 移动到下一个节点
    }

    printf("\n");

    // 使用for循环
    for(curr = &root; curr != NULL; curr = curr->next)
    {
        printf("%d\n",curr->x); // 输出当前节点的值
    }


    // 释放内存
    free(root.next->next); // 释放最后一个节点
    free(root.next); // 释放倒数第二个节点
    // 注意：顺序不能颠倒
    
    return 0;
}