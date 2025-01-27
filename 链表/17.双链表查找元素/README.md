# 查找元素 (双链表)

## 代码示例

## 循环方法

### 遍历链表

```c
Node *find_element(Node *tail, int value)
{
    for (Node *curr = tail; curr != NULL; curr = curr->next) {   }
}
```

### 判断当前节点是否为需要查找的节点

```c
Node *find_element(Node *tail, int value)
{
    for (Node *curr = tail; curr != NULL; curr = curr->next)
    {
        if (curr->x == value) {   }
    }
}
```

### 返回当前节点

```c
Node *find_element(Node *tail, int value)
{
    for (Node *curr = tail; curr != NULL; curr = curr->next)
    {
        if (curr->x == value)
        {
            return curr;
        }
    }
    return NULL; // 没找到的情况
}
```

[源代码](双链表查找元素.c#L11)

## 递归方法

### 判断退出条件

```c
Node *find_element_recursive(Node *node ,int value)
{
    if (node->x == value)
    {
        return node; // 找到的情况
    }
}
```

### 递归调用

```c
Node *find_element_recursive(Node *node ,int value)
{
    if (node->x == value)
    {
        return node; // 找到的情况
    }

    return find_element_recursive(node->next, value); // 递归调用
}
```

#### 这里出现的问题

如果遍历完整个链表都没有找到，会导致段错误

#### 解决方案——添加检测

```diff
Node *find_element_recursive(Node *node,int value)
{
+    if (node == NULL)
+    {
+        return NULL;
+    }

    if (node->x == value)
    {
        return node; // 找到的情况
    }

    return find_element_recursive(node->next, value); // 递归调用
}
```

### 完整代码

```c
Node *find_element_recursive(Node *node ,int value)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (node->x == value)
    {
        return node;
    }

    return find_element_recursive(node->next, value);   
}
```

[源代码](双链表查找元素.c#L23)