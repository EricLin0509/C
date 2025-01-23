# 任意位置插入元素 (双链表)

## 代码示例

### 初始化节点

```c
void insert_after(Node *node, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }
    new_node->x = value;
}
```

### 插入节点

```c
void insert_after(Node *node, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }
    new_node->x = value;

    new_node->prev = node; // 新节点的前一个节点为 node
    new_node->next = node->next; // 新节点的后一个节点为 node 的后一个节点
}
```

### 修改前后节点的指针

```c
void insert_after(Node *node, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }
    new_node->x = value;

    new_node->prev = node; // 新节点的前一个节点为 node
    new_node->next = node->next; // 新节点的后一个节点为 node 的后一个节点

    node->next->prev = new_node; // node 的后一个节点为新节点
    node->next = new_node; // node 的后一个节点为新节点
}
```

#### 这里出现的问题

如果 `node` 的后一个节点为 `NULL`，执行 `node->next = new_node` 会出现段错误

#### 解决方案——添加检测

```diff
void insert_after(Node *node, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }
    new_node->x = value;

    new_node->prev = node; // 新节点的前一个节点为 node
    new_node->next = node->next; // 新节点的后一个节点为 node 的后一个节点

-    node->next->prev = new_node; // node 的后一个节点为新节点
+    if (node->next != NULL)
+    {
+        node->next->prev = new_node; // node 的后一个节点为新节点
+    }
    node->next = new_node; // node 的后一个节点为新节点
}
```

### 完整代码

```c
void insert_after(Node *node, int value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(1);
    }
    new_node->x = value;

    new_node->prev = node; // 新节点的前一个节点为 node
    new_node->next = node->next; // 新节点的后一个节点为 node 的后一个节点

    node->next->prev = new_node; // node 的后一个节点为新节点
    if (node->next != NULL)
    {
        node->next->prev = new_node; // node 的后一个节点为新节点
    }
    node->next = new_node; // node 的后一个节点为新节点
}
```

[源代码](双链表任意位置插入元素.c#L11)