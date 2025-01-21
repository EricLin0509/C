# 释放双链表

## 步骤

1. 从第二个节点开始遍历链表
2. 每次遍历都释放前一个节点
3. 最后释放最后一个节点

## 代码示例

### 初始化节点

```c
void deallocate(Node **tail, Node **head)
{
    Node *curr = *tail;
}
```

### 遍历双链表

```c
void deallocate(Node **tail, Node **head)
{
    Node *curr = *tail;

    while (curr != NULL) {   }
}
```

### 释放节点

```c
void deallocate(Node **tail, Node **head)
{
    Node *curr = *tail;

    while (curr != NULL) 
    {
        curr = curr->next;
        free(curr->prev);
    }
}
```

### 释放最后一个节点

```c
void deallocate(Node **tail, Node **head)
{
    Node *curr = *tail;

    while (curr != NULL) 
    {
        curr = curr->next;
        free(curr->prev);
    }
    free(curr);
}
```

### 重置`tail`和`head`


```c
void deallocate(Node **tail, Node **head)
{
    Node *curr = *tail;

    while (curr != NULL) 
    {
        curr = curr->next;
        free(curr->prev);
    }
    free(curr);

    *tail = NULL;
    *head = NULL;
}
```

#### 这里出现的问题

如果 `tail` 和 `head` 都指向 `NULL`，执行 `free(curr-prev)` 会出现段错误

#### 解决方案——添加检测

```diff
void deallocate(Node **tail, Node **head)
{
+    if (*tail == NULL)
+    {
+        return;
+    }
    Node *curr = *tail;

    while (curr != NULL) 
    {
        curr = curr->next;
        free(curr->prev);
    }
    free(curr);

    *tail = NULL;
    *head = NULL;
}
```

### 完整代码

```c
void deallocate(Node **tail, Node **head)
{
    if (*tail == NULL)
    {
        return;
    }
    Node *curr = *tail;

    while (curr->next != NULL) 
    {
        curr = curr->next;
        free(curr->prev);
    }
    free(curr);

    *tail = NULL;
    *head = NULL;
}
```

[源代码](释放双链表.c#L11)