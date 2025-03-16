#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack
{
    int *collection;
    int capacity;
    int size;
} Stack;

Stack *create_stack(int capacity)
{
    if (capacity <= 0)
    {
        perror("capacity must be greater than 0");
        return NULL;
    }
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL)
    {
        perror("malloc stack");
        return NULL;
    }

    stack->collection = malloc(sizeof(int) * capacity);
    if (stack->collection == NULL)
    {
        perror("malloc collection");
        free(stack); // 释放已经分配的内存
        return NULL;
    }

    stack->capacity = capacity;
    stack->size = 0;
    return stack;
}

void destroy_stack(Stack *stack)
{
    free(stack->collection);
    free(stack);
}

bool is_empty(Stack *stack)
{
    return stack->size == 0;
}

bool is_full(Stack *stack)
{
    return stack->size == stack->capacity;
}

bool push(Stack *stack, int element)
{
    if (is_full(stack))
    {
        return false; // 栈已满
    }

    stack->collection[stack->size] = element;
    stack->size++; // 栈的大小加 1

    return true; // 入栈成功
}

bool peek(Stack *stack, int *element)
{
    if (is_empty(stack))
    {
        return false; // 栈为空
    }

    *element = stack->collection[stack->size - 1];

    return true; // 栈不为空
}

bool pop(Stack *stack, int *element)
{
    if (is_empty(stack))
    {
        return false; // 栈为空
    }

    stack->size--; // 栈的大小减 1
    *element = stack->collection[stack->size];

    return true; // 出栈成功
}

int main(int argc, const char * argv[]) {
    Stack *stack = create_stack(5);

    if (is_empty(stack))
    {
        printf("Stack is empty!\n");
    }

    push(stack, 2);
    printf("Stack size: %d\n", stack->size);

    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    push(stack, 6);

    if (is_full(stack))
    {
        printf("Stack is full!\n");
    }

    bool try = push(stack, 7);
    if (!try)
    {
        printf("Push failed!\n");
    }
    
    int peek_value = 0;

    peek(stack, &peek_value);
    printf("Peek value: %d\n", peek_value);

    
    int pop_value = 0;
    pop(stack, &pop_value);
    printf("Pop value: %d\n", pop_value);
    printf("Stack size: %d\n", stack->size);

    destroy_stack(stack);
    
    return 0;
}