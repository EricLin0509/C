# 添加元素

## 之前的方法

```c
    Node root;
    root.x = 1;
    root.next = malloc(sizeof(Node));
    root.next->x = 2;
    root.next->next = malloc(sizeof(Node));
    root.next->next->x = 3;
    root.next->next->next = NULL;
```
### 缺点
1. 代码冗长
2. 容易出错

#### 例如添加10个元素

```c
    Node root;
    root.x = 1;
    root.next = malloc(sizeof(Node));
    root.next->x = 2;
    root.next->next = malloc(sizeof(Node));
    root.next->next->x = 3;
    root.next->next->next = malloc(sizeof(Node));
    root.next->next->next->x = 4;
    root.next->next->next->next = malloc(sizeof(Node));
    root.next->next->next->next->x = 5;
    root.next->next->next->next->next = malloc(sizeof(Node));
    root.next->next->next->next->next->x = 6;
    root.next->next->next->next->next->next = malloc(sizeof(Node));
    root.next->next->next->next->next->next->x = 7;
    root.next->next->next->next->next->next->next = malloc(sizeof(Node));
    root.next->next->next->next->next->next->next->x = 8;
    root.next->next->next->next->next->next->next->next = malloc(sizeof(Node));
    root.next->next->next->next->next->next->next->next->x = 9;
    root.next->next->next->next->next->next->next->next->next = malloc(sizeof(Node));
    root.next->next->next->next->next->next->next->next->next->x = 10;
```

这里可以看到，代码的重复率很高，而且容易出错

## 解决代码的重复率很高的方案——函数

## 尾插法

### 创建新节点

```c
void insert(Node **root, int value)
{
    Node *newNode = malloc(sizeof(Node)); // 创建新节点
    newNode->next = NULL;
    newNode->x = value;
}
```

#### 为什么不用二级指针？

由于需要改变整个节点的地址，所以需要用二级指针

#### 这里出现的问题

如果 `malloc` 失败，会返回 NULL，但是我们没有处理这种情况

#### 解决方案——添加错误处理

```c
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
}
```

### 将新节点添加到链表中
```c
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

    Node *curr = *root;
    while (curr->next != NULL) // 找到最后一个节点
    {
        curr = curr->next;
    }
    curr->next = newNode; // 将新节点添加到链表中
}
```

#### 假如链表为空
```c
    Node *root_empty = NULL;
    insert(&root_empty, 1);
```

执行

```zsh
./a.out
zsh: segmentation fault (core dumped)  ./a.out
```

出现了段错误，因为 `root_empty` 是 NULL，我们不能访问 `root_empty->next`

#### 解决方案——添加检测机制
```c
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
```

[源代码](添加元素尾插法.c#L9)

### 优点

1. 链表的顺序与插入顺序相同

### 缺点

1. 需要遍历链表
2. 插入速度慢

## 头插法

### 创建新节点

```c
void insert_begin(Node **root, int value)
{
    Node *newNode = malloc(sizeof(Node)); // 创建新节点

    if (newNode == NULL) // 如果内存分配失败
    {
        printf("malloc failed\n");
        exit(1);
    }

    newNode->x = value;
    newNode->next = *root;
}
```

### 将新节点添加到头部

```c
void insert_begin(Node **root, int value)
{
    Node *newNode = malloc(sizeof(Node)); // 创建新节点

    if (newNode == NULL) // 如果内存分配失败
    {
        printf("malloc failed\n");
        exit(1);
    }

    newNode->x = value;
    newNode->next = *root;

    *root = newNode; // 将新节点作为根节点
}
```
[源代码](添加元素头插法.c#L9)

### 优点

1. 由于不需要遍历链表，因此插入速度快
2. 不需要判断链表是否为空

### 缺点

1. 链表的顺序与插入顺序相反

## 尾插法与头插法的比较
| 方法 | 优点 | 缺点 |
| :---: | :---: | :---: |
| 尾插法 | 1. 链表的顺序与插入顺序相同 | 1. 需要遍历链表<br>2. 插入速度慢 |
| 头插法 | 1. 插入速度快<br>2. 不需要判断链表是否为空 | 1. 链表的顺序与插入顺序相反 |