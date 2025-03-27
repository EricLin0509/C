#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *val;
    int head;
    int tail;
    int num_entries;
    int size;
} queue;

void init_queue(queue *q, int max_size)
{
    q->size = max_size;
    q->val = (int *)malloc(sizeof(int) * max_size);
    q->num_entries = 0;
    q->head = 0;
    q->tail = 0;
}

bool is_empty(queue *q)
{
    return q->num_entries == 0;
}

bool is_full(queue *q)
{
    return q->num_entries == q->size;
}

void destroy_queue(queue *q)
{
    free(q->val);
    q->head = 0;
    q->tail = 0;
}

bool enqueue(queue *q, int val)
{
    if (is_full(q))
    {
        perror("queue is full");
        return false;
    }
    q->val[q->tail] = val; // 添加元素
    q->num_entries++; // 元素个数加1
    q->tail = (q->tail + 1) % q->size; // 尾指针后移
    return true;
}

int dequeue(queue *q)
{
    int result;

    if (is_empty(q))
    {
        perror("queue is empty");
        return -1;
    }

    result = q->val[q->head]; // 取出元素
    q->num_entries--; // 元素个数减1
    q->head = (q->head + 1) % q->size; // 头指针后移
    return result;
}

int main(int argc, const char * argv[]) {

    queue *q = malloc(sizeof(queue));
    init_queue(q, 5);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);

    int tmp;
    while ((tmp = dequeue(q)) != -1)
    {
        printf("%d\n", tmp);
    }
    destroy_queue(q);
    free(q);

    return 0;
}