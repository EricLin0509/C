# 删除元素

## 步骤

1. 找到要删除的元素
2. 将前一个元素的 next 指向后一个元素
3. 释放要删除的元素

## 代码示例

```c
void remove_element(Node **root, int value) {}
```

`int value` 是要删除的元素的值

### 检查链表是否为空

```c
void remove_element(Node **root, int value)
{
    if (*root == NULL)
    {
        return;
    }
}
```

### 遍历链表

```c
void remove_element(Node **root, int value)
{
    if (*root == NULL)
    {
        return;
    }

    for (Node *curr = *root; curr->next != NULL; curr = curr->next) {}
}
```

### 找到要删除的元素

```c
void remove_element(Node **root, int value)
{
    if (*root == NULL)
    {
        return;
    }

    for (Node *curr = *root; curr->next != NULL; curr = curr->next)
    {
        if (curr->next->x == value) {}
    }
}
```

### 修改链表

```c
void remove_element(Node **root, int value)
{
    if (*root == NULL)
    {
        return;
    }

    for (Node *curr = *root; curr->next != NULL; curr = curr->next)
    {
        if (curr->next->x == value)
        {
            Node *need_remove = curr->next; // 要删除的元素
            curr->next = curr->next->next; // 修改链表
            free(need_remove); // 释放要删除的元素
        }
    }
}
```

### 这里出现的问题

因为此函数判断时都是读取下一个元素，所以当尝试删除第一个元素时，会出现问题

#### 解决方案——添加特殊情况

```c
void remove_element(Node **root, int value)
{
    if (*root == NULL)
    {
        return;
    }

    if ((*root)->x == value)
    {
        Node *need_remove = *root; // 要删除的元素
        *root = (*root)->next; // 修改链表
        free(need_remove); // 释放要删除的元素
        return;
    }

    for (Node *curr = *root; curr->next != NULL; curr = curr->next)
    {
        if (curr->next->x == value)
        {
            Node *need_remove = curr->next; // 要删除的元素
            curr->next = curr->next->next; // 修改链表
            free(need_remove); // 释放要删除的元素
            return;
        }
    }
}
```

[源代码](删除元素.c#L9)