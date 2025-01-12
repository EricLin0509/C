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

int main(int argc, const char * argv[]) {

    Node *root = NULL;
    insert_begin(&root, 1);
    insert_begin(&root, 2);

    for (Node *curr = root; curr != NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }

    return 0;
}