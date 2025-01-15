#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

void remove_element(Node **root, int value)
{
    if (*root == NULL)
    {
        return;
    }

    if ((*root)->x == value)
    {
        Node *need_remove = *root; // 要删除的元素
        *root = (*root)->next; // 修改链表
        free(need_remove); // 释放要删除的元素
        return;
    }

    for (Node *curr = *root; curr->next != NULL; curr = curr->next)
    {
        if (curr->next->x == value)
        {
            Node *need_remove = curr->next; // 要删除的元素
            curr->next = curr->next->next; // 修改链表
            free(need_remove); // 释放要删除的元素
            return;
        }
    }
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

    Node *root = NULL;

    insert(&root, 1);
    insert(&root, 3);
    insert(&root, 6);

    for (Node *curr = root; curr != NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }
    printf("\n");

    remove_element(&root, 3);
    
    for (Node *curr = root; curr != NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }
    printf("\n");

    remove_element(&root, 1);

    for (Node *curr = root; curr!= NULL; curr = curr->next)
    {
        printf("%d\n", curr->x);
    }

    deallocate(&root);

    return 0;
}