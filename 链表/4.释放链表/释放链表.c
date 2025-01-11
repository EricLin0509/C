#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

void deallocate(Node **root)
{
    Node *curr = *root;
    while(curr != NULL) // 遍历链表
    {
        Node *temp = curr; // 保存当前节点的地址
        curr = curr->next;
        free(temp); // 释放当前节点
    }
    *root = NULL; // 重置头节点
    printf("deallocated\n");
}

void instert(Node **root, int value)
{
    Node *newNode = malloc(sizeof(Node)); // 创建新节点
    
    if (newNode == NULL)
    {
        printf("malloc failed\n");
        exit(1); // 退出程序，1 表示错误
    }
    
    newNode->next = NULL;
    newNode->x = value;

    if (*root == NULL) // 如果链表为空
    {
        *root = newNode; // 将新节点作为根节点
        return; // 结束函数
    }

    Node *curr = *root;
    while (curr->next != NULL) // 找到最后一个节点
    {
        curr = curr->next;
    }
    curr->next = newNode; // 将新节点添加到链表中
}

int main(int argc, const char * argv[]) {

    Node *root = malloc(sizeof(Node)); // 创建头节点
    if (root == NULL) // 判断是否创建成功
    {
        exit(1);
    }
    root->x = 1;
    root->next = NULL;

    instert(&root, 2);

    for (Node *curr = root; curr != NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }
    printf("\n");

    deallocate(&root); // 释放链表

    return 0;
}