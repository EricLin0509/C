#include <stdio.h>
#include <stdlib.h>

typedef struct Node { // 定义节点
    int data; // 数据域
    struct Node *next; // 指针域
    // Node *next; // 错误，因为此时还没有定义Node
} Node;

int main(int argc, const char*argv[]) {

    Node root1, node1; // 定义根节点
    root1.data = 15;
    root1.next = &node1; // 根节点的指针域指向node1

    node1.data = 20;
    node1.next = NULL; // 结束

    printf("First: %d\n", root1.data);
    printf("Second: %d\n", node1.data);
    printf("Second: %d\n", root1.next->data); // 等价于node1.data


    // 不使用多个节点变量

    Node root2;
    root2.data = 5;
    root2.next = malloc(sizeof(Node)); // 分配内存

    root2.next->data = 10; // 赋值
    root2.next->next = NULL; // 结束

    printf("First: %d\n", root2.data);
    printf("Second: %d\n", root2.next->data); // 等价于node1.data

    free(root2.next); // 释放内存
    return 0;
}