#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

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

int main(int argc, const char * argv[]) {

    Node *root = malloc(sizeof(Node)); // 创建头节点
    if (root == NULL) // 判断是否创建成功
    {
        exit(1);
    }
    root->x = 1;
    root->next = NULL;

    insert(&root, 2);

    for (Node *curr = root; curr != NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }
    printf("\n");


    Node *root_empty = NULL; // 空链表
    insert(&root_empty, -2);
    for (Node *curr = root_empty; curr!= NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }

    return 0;
}