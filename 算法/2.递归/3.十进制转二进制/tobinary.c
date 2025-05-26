#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node; // 定义链表节点，实现栈

Node* tobinary(int m, Node *stack)
{
    if (m == 0) return stack;
    Node *node = malloc(sizeof(Node));
    node->data = m % 2;
    node->next = stack;
    return tobinary(m / 2, node);
}

int main(int argc, const char *argv[]) {
    int m = 233;
    Node *stack = NULL;
    stack = tobinary(m, stack);
    while (stack != NULL)
    {
        printf("%d", stack->data);
        stack = stack->next;
    }
    printf("\n");
    return 0;
}