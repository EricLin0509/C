#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

void insert_begin(Node **root, int value)
{
    Node *newNode = malloc(sizeof(Node)); // 创建新节点

    if (newNode == NULL) // 如果内存分配失败
    {
        printf("malloc failed\n");
        exit(1);
    }

    newNode->x = value;
    newNode->next = *root;

    *root = newNode; // 将新节点作为根节点
}

void insert_after(Node *node, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return;
    }

    newNode->x = value;
    newNode->next = node->next; // 新节点的指针域存储下一个节点的地址
    node->next = newNode; // 上一个节点的指针域存储新节点的地址
}

void insert_sorted(Node **root, int value)
{
    if (*root == NULL || value <= (*root)->x)
    {
        insert_begin(root, value);
        return; // 退出函数
    }

    Node *curr = *root;
    while(curr->next != NULL)
    {
        if (value <= curr->next->x) // 找到插入位置
        {
            break; // 退出循环
        }
        curr = curr->next;
    }
    insert_after(curr, value);
}

int main(int argc, const char * argv[]) {

    Node *root = NULL;
    insert_sorted(&root, 5);
    insert_sorted(&root, 10);
    insert_sorted(&root, 1);
    insert_sorted(&root, 7);
    insert_sorted(&root, 4);

    for (Node *curr = root; curr != NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }
    
    return 0;
}