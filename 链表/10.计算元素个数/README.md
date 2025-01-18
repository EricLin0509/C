# 计算元素个数

## 步骤

1. 遍历链表
2. 计算元素个数

## 代码示例

## 循环

### 遍历链表

```c
int count(Node *node)
{
    for (Node *curr = node; curr != NULL; curr = curr->next) {  }
}
```

### 创建变量并计数

```c
int count(Node *node)
{
    int c = 0;
    for (Node *curr = node; curr != NULL; curr = curr->next)
    {
        c++;
    }
    return c;
}
```

[源代码](计算元素个数.c#L10)

## 递归

### 确定递归结束条件

```c
int count_recursive(Node *node)
{
    if (root == NULL)
    {
        return 0;
    }
}
```

### 递归调用

```c
int count_recursive(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return 1 + count_recursive(node->next);
}
```
[源代码](计算元素个数.c#L20)