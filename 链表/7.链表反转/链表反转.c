#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

void reverse(Node **root)
{
    Node *prev = NULL; // 前一个节点
    Node *curr = *root; // 当前节点

    while(curr != NULL)
    {
        Node *next = curr->next; // 下一个节点

        curr->next = prev; // 反转当前节点的指针
        prev = curr; // 前一个节点移动到当前节点
        curr = next; // 当前节点移动到下一个节点
    }
    *root = prev; // 更新根节点
}

void insert(Node **root, int value)
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
}

int main(int argc, const char * argv[]) {

    Node *root = NULL;;
    insert(&root, 1);
    insert(&root, 3);
    insert(&root, 6);
    insert(&root, 9);

    for (Node *curr = root; curr != NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }
    printf("\n");

    reverse(&root);

    for (Node *curr = root; curr != NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }

    deallocate(&root);

    return 0;
}