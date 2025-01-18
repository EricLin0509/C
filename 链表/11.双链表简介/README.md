# 双链表简介

## 定义

双链表是一种链式存储结构，它的每个节点都有两个指针，分别指向它的前驱节点和后继节点

## 特点
1. 双链表的每个节点都有两个指针，分别指向它的前驱节点和后继节点
2. 双链表的头节点的前驱指针指向NULL，尾节点的后继指针指向NULL

### 优点
1. 双链表的插入和删除操作都非常方便
2. 双链表的查找操作也非常方便

### 缺点
1. 双链表的每个节点都需要占用更多的内存空间

## 图示

![双链表](../imgs/link5.png)

## 与单链表的比较

| 单链表 | 双链表 |
| :------: | :------: |
| 每个节点只有一个指针 | 每个节点有两个指针 |
| 查找操作需要遍历链表 | 查找操作可以从任意节点开始遍历 |
| 占用内存空间较少 | 占用内存空间较多 |

## 代码示例

### 定义节点格式

```c
typedef struct Node {

    int x; // 数据
    struct Node *prev; // 前驱指针
    struct Node *next; // 后继指针
} Node;
```

### 创建节点

```c
int main(int argc, const char * argv[]) {

    Node *tail = malloc(sizeof(Node)); // 创建尾节点

    if (tail == NULL) // 如果内存分配失败
    {
        return 1;
    }
    tail->x = 1;
}
```

### 连接下一个节点

```c
int main(int argc, const char * argv[]) {

    Node *tail = malloc(sizeof(Node)); // 创建尾节点

    if (tail == NULL) // 如果内存分配失败
    {
        return 1;
    }
    tail->x = 1;

    tail->prev = NULL; // 前驱指针指向NULL
    tail->next = malloc(sizeof(Node)); // 创建下一个节点
    if (tail->next == NULL) // 如果内存分配失败
    {
        return 1;
    }
    tail->next->x = 2; // 数据赋值
    tail->next->prev = tail; // 前驱指针指向尾节点
    tail->next->next = NULL; // 后继指针指向NULL
}
```

### 确定链表的头节点

```c
int main(int argc, const char * argv[]) {

    Node *tail = malloc(sizeof(Node)); // 创建尾节点

    if (tail == NULL) // 如果内存分配失败
    {
        return 1;
    }
    tail->x = 1;

    tail->prev = NULL; // 前驱指针指向NULL
    tail->next = malloc(sizeof(Node)); // 创建下一个节点
    if (tail->next == NULL) // 如果内存分配失败
    {
        return 1;
    }
    tail->next->x = 2; // 数据赋值
    tail->next->prev = tail; // 前驱指针指向尾节点
    tail->next->next = NULL; // 后继指针指向NULL

    Node *head = tail->next->next; // 头节点
}
```

[源代码](双链表简介.c)