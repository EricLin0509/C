#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

bool isCycle(Node *root)
{
    Node *slow = root; // 慢指针
    Node *fast = root; // 快指针

    while (slow != NULL && fast != NULL && fast->next != NULL)
    {
        slow = slow->next; // 慢指针前进一步
        fast = fast->next->next; // 快指针前进两步

        if (slow == fast)
        {
            return true;
        }
    }
    
    return false;
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

    root->next->next->next->next = root->next; // 创建环形链表

    if (isCycle(root))
    {
        printf("此链表有环\n");
    }
    else
    {
        printf("此链表无环\n");
    }

    return 0;
}