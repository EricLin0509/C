# 队列简介

## 定义

队列是一种特殊的线性表，特殊之处在于它只允许在**表的前端（front）进行删除操作**，而在**表的后端（rear）进行插入操作**，和栈一样，队列是一种操作受限制的线性表。进行插入操作的端称为队尾，进行删除操作的端称为队头

- 入队 (Enqueue)：把元素添加到队列中
- 出队 (Dequeue)：把元素从队列中移除

## 代码示例

### 定义队列

```c
int queue[256];
int size = 0;
```

### 入队

```c
void insert(int element)
```

#### 检查队列是否已满

```c
void insert(int element)
{
    if (size == 256)
    {
        perror("queue is full");
        return;
    }
}
```

#### 插入元素

```c
void insert(int element)
{
    if (size == 256)
    {
        perror("queue is full");
        return;
    }

    queue[size] = element;
    size++;
}
```

### 出队

```c
int remove()
```

#### 检查队列是否为空

```c
int remove()
{
    if (size == 0)
    {
        perror("queue is empty");
        return -1;
    }
}
```

#### 移除元素

我们只需要将第一个后面的元素往前移动一位即可

```c
int remove()
{
    if (size == 0)
    {
        perror("queue is empty");
        return -1;
    }

    int element = queue[0];
    for (int i = 0; i < size - 1; i++)
    {
        queue[i] = queue[i + 1];
    }
    size--;
    return element;
}