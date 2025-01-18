#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

int count(Node *node)
{
    int c = 0;
    for (Node *curr = node; curr != NULL; curr = curr->next)
    {
        c++;
    }
    return c;
}

int count_recursive(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return 1 + count_recursive(node->next);
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


int main(int argc, const char * argv[]) {

    Node *root = NULL;;
    insert(&root, 1);
    insert(&root, 3);
    insert(&root, 6);
    insert(&root, 9);

    printf("此链表有%d个元素\n", count(root));
    printf("此链表有%d个元素\n", count_recursive(root));

    return 0;
}