#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// 队列

// 队列是一种特殊的线性表
// 特殊之处在于它只允许在表的前端（front）进行删除操作
//而在表的后端（rear）进行插入操作，和栈一样
//队列是一种操作受限制的线性表。进行插入操作的端称为队尾，进行删除操作的端称为队头

/*

4 --- 队头
v
5
v
6 --- 队尾

*/

// 插入一个新的元素 (排队)
/*

4 --- 队头
v
5
v
6
v
7 --- 新队尾

*/


typedef struct Node // 用于表示节点
{
    int value; // 数据域
    struct Node *next; // 指针域
    /*
    数据域：存储数据
    指针域：存储下一个节点的地址
    */
}Node;

typedef struct
{
    Node *head; // 头指针 (对头)
    Node *tail; // 尾指针 (对尾)
    int size; // 队列的长度
}Queue;

Queue *create_queue(); // 创建新的队列
int get_size(Queue *queue); // 获取队列的长度
bool is_empty(Queue *queue); // 判断队列是否为空
int peek(Queue *queue, bool *status); // 获取队头元素，如果队列为空，返回0
void  enqueue(Queue *queue, int value); // 入队
int dequeue(Queue *queue, bool *status); // 出队
void destroy_queue(Queue *queue); // 销毁队列

int main(int argc, const char * argv[]) {

    Queue *queue = create_queue(); // 创建新的队列
    if (is_empty(queue))
    {
        printf("队列为空\n");
    }
    
    enqueue(queue, 4); // 入队，长度为1
    if (!is_empty(queue))
    {
        printf("队列不为空\n");
    }
    enqueue(queue, 5); // 入队，长度为2
    enqueue(queue, 6); // 入队，长度为3
    printf("队列长度为：%d\n", get_size(queue)); // 输出队列长度

    bool status = false;
    int value;
    value = peek(queue, &status); // 获取队头元素
    if (status)
    {
        printf("队头元素为：%d\n", value);
    }

    value = dequeue(queue, &status); // 出队，长度为4
    if (status)
    {
        printf("出队成功，出队值为%d\n", value);
    }

    destroy_queue(queue); // 销毁队列
    printf("队列已销毁\n");

    return 0;
}


Queue *create_queue()
{
    Queue *queue = malloc(sizeof(Queue)); // 分配内存空间

    queue->head = NULL; // 初始化头指针
    queue->tail = NULL; // 初始化尾指针
    queue->size = 0; // 初始化队列长度为0

    return queue;
}

int get_size(Queue *queue)
{
    return queue->size; // 返回队列长度
}

bool is_empty(Queue *queue)
{
    return (queue->size == 0); // 判断队列长度是否为0
}

int peek(Queue *queue, bool *status)
{
    if (is_empty(queue))
    {
        *status = false; // 如果队列为空，设置状态为false
        return 0; // 返回空值
    }
    *status = true; // 设置状态为true
    return queue->head->value; // 返回队头元素的值
}

void enqueue(Queue *queue, int value)
{
    Node *new_node = malloc(sizeof(Node)); // 分配内存空间
    new_node->value = value; // 设置新节点的值
    new_node->next = NULL; // 初始化新节点的指针域为NULL

    if (is_empty(queue)) // 如果队列为空
    {
        queue->head = new_node; // 将新节点设置为队头
        queue->tail = new_node; // 将新节点设置为队尾
    }
    else
    {
        queue->tail->next = new_node; // 将新节点插入到队尾
        queue->tail = new_node; // 更新队尾指针
    }
    queue->size++; // 队列长度加1
}

int dequeue(Queue *queue, bool *status)
{
    if (is_empty(queue)) // 如果队列为空
    {
        *status = false; // 设置状态为false
        return 0 ; // 返回空值
    }
    *status = true; // 设置状态为true

    int value = queue->head->value; // 获取队头元素的值

    // 删除队头节点
    Node *old_head = queue->head; // 保存旧的队头节点

    if (queue->head == 1) // 如果队列为1
    {
        queue->head = NULL; // 将队头指针设置为NULL，因为队列为空
        queue->tail = NULL; // 将队尾指针设置为NULL，因为队列为空
    }
    else
    {
        queue->head = queue->head->next; // 更新队头指针
    }
        
    free(old_head); // 释放旧的队头节点的内存空间
    queue->size--; // 队列长度减1

    return value; // 返回队头元素的值
}

void destroy_queue(Queue *queue)
{
    Node *currentnode = queue->head; // 保存当前节点

    while (currentnode != NULL) // 遍历队列
    {
        Node *temp = currentnode; // 保存下一个节点
        currentnode = currentnode->next; // 更新当前节点
        free(temp); // 释放当前节点的内存空间
    }
    free(queue); // 释放队列的内存空间
}