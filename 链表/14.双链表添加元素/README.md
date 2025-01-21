# 添加元素 (双链表)

## 代码示例

## 头插法

### 创建新节点

```c
void insert_begining(Node **tail, int value)
{
    Node *new_node = malloc(sizeof(Node));
}
```

### 检查内存分配是否成功

```c
void insert_begining(Node **tail, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        exit(1);
    }
}
```

### 将新节点插入到链表的开头

```c
void insert_begining(Node **tail, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        exit(1);
    }

    new_node->x = value; // 新节点的值
    new_node->prev = NULL; // 新节点的前一个节点为 NULL
    new_node->next = *tail; // 插入到链表的开头
    (*tail)->prev = new_node; // 新节点的下一个节点为原来的尾节点
    *tail = new_node; // 新节点变成新的尾节点
}
```

#### 这里出现的问题

如果链表为空，那么尾节点为 NULL，那么就会出现错误

#### 解决方案——添加检测

```diff
void insert_begining(Node **tail, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        exit(1);
    }

    new_node->x = value; // 新节点的值
    new_node->prev = NULL; // 新节点的前一个节点为 NULL
    new_node->next = *tail; // 插入到链表的开头
-    (*tail)->prev = new_node; // 新节点的下一个节点为原来的尾节点
+    if (*tail != NULL) 
+    {
+        (*tail)->prev = new_node; // 新节点的下一个节点为原来的尾节点
+    }
    *tail = new_node; // 新节点变成新的尾节点
}
```

### 完整代码

```c
void insert_begining(Node **tail, int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        exit(1);
    }

    new_node->x = value; // 新节点的值
    new_node->prev = NULL; // 新节点的前一个节点为 NULL
    new_node->next = *tail; // 插入到链表的开头
    if (*tail != NULL) 
    {
        (*tail)->prev = new_node; // 新节点的下一个节点为原来的尾节点
    }
    *tail = new_node; // 新节点变成新的尾节点
}
```

[源代码](双链表添加元素.c#L11)

假如我们以下面的代码初始化一个空链表

```c
    Node *tail = NULL;
    Node *head = NULL;
```

 `tail` 和 `head` 都为 NULL，那么在遍历链表时就会出现问题

## 初始化空链表

### 创建新节点

```c
void init(Node **tail, Node **head, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }
}
```

### 初始化新节点

```c
void init(Node **tail, Node **head, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }

    new_node->x = value;
    new_node->prev = NULL;
    new_node->next = NULL;
}
```

### 设置尾节点和头节点

```c
void init(Node **tail, Node **head, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }

    new_node->x = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    *tail = new_node; // 尾节点为新节点
    *head = new_node; // 头节点为新节点
}
```

[源代码](双链表添加元素.c#L30)

### 调用函数

```c
    Node *tail = NULL;
    Node *head = NULL;

    init(&tail, &head, 1);
    insert_begining(&tail, 2);
    insert_begining(&tail, 3);
    insert_begining(&tail, 4);
```

[源代码](双链表添加元素.c#L48)