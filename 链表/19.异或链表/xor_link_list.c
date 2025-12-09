#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

typedef struct Node {
    int value; // 值
    uintptr_t xor_ptr; // 用于异或运算的指针
} Node;

typedef struct XORLinkedList {
    Node *head; // 头节点
    Node *tail; // 尾节点
} XORLinkedList;

Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
    node->value = value;
    node->xor_ptr = 0; // 0 表示没有前驱节点或后继节点

    return node;
}

void add_node(XORLinkedList *list, int value)
{
    if (list->head == NULL) // 链表为空
    {
        assert(list->tail == NULL); // 确保链表为空

        Node *node = create_node(value);
        list->head = node;
        list->tail = node;
        return;
    }
    else // 链表不为空
    {
        Node *node = create_node(value);
        node->xor_ptr = (uintptr_t)list->tail; // 指向尾节点
        list->tail->xor_ptr ^= (uintptr_t)node; // 尾节点指向新节点
        list->tail = node; // 更新尾节点
    }
}

Node *get_next_node(Node *node, uintptr_t *prev_xor_ptr)
{
    Node *next_node = (Node *)((uintptr_t)node->xor_ptr ^ *prev_xor_ptr);
    *prev_xor_ptr = (uintptr_t)node; // 更新 prev_xor_ptr

    return next_node;
}

void traverse_list(XORLinkedList *list)
{
    Node *node = list->head;
    uintptr_t prev_xor_ptr = 0; // 初始 prev_xor_ptr 为 0

    for (Node *iter = list->head; iter != NULL; iter = get_next_node(iter, &prev_xor_ptr))
    {
        // 处理当前节点
        printf("%d ", iter->value);
    }
    printf("\n");
}

int main(void) {
    XORLinkedList list = { 0 };

    for (int i = 1; i <= 5; i++)
    {
        add_node(&list, i);
    }

    traverse_list(&list);

    return 0;
}