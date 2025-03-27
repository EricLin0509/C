# 环形队列

## 定义

环形队列是一种特殊的队列，它的头尾相连，形成一个环

## 实现

```c
typedef struct
{
    int *val;
    int head;
    int tail;
    int num_entries;
    int size;
} queue;
```

- `val`：数组
- `head`：头指针
- `tail`：尾指针
- `num_entries`：队列中元素的个数
- `size`：队列的大小

### 初始化队列

**需要传入队列的大小**

**头尾指针初始化为0**

```c
void init_queue(queue *q, int max_size)
{
    q->size = max_size;
    q->val = (int *)malloc(sizeof(int) * max_size);
    q->num_entries = 0;
    q->head = 0;
    q->tail = 0;
}
```

### 检查队列是否为空

```c
bool is_empty(queue *q)
{
    return q->num_entries == 0;
}
```

### 检查队列是否已满

```c
bool is_full(queue *q)
{
    return q->num_entries == q->size;
}
```

### 销毁队列

```c
void destroy_queue(queue *q)
{
    free(q->val);
    q->head = 0;
    q->tail = 0;
}
```

### 入队

```c
bool enqueue(queue *q, int val)
```

#### 入队前检查队列是否已满

```c
bool enqueue(queue *q, int val)
{
    if (is_full(q))
    {
        perror("queue is full");
        return false;
    }
    return true;
}
```

#### 添加元素

```c
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
```

### 出队

```c
int dequeue(queue *q)
```

#### 出队前检查队列是否为空

```c
int dequeue(queue *q)
{
    int result;

    if (is_empty(q))
    {
        perror("queue is empty");
        return -1;
    }
    return result;
}
```

#### 取出元素

```c
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
```

### 测试

```c
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
```

```bash
gcc -o queue queue.c
./queue
1
2
3
4
5
queue is empty: Success
```