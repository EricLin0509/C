# 链表排序

## 步骤

1. 找到目前节点应该插入的位置
2. 插入该节点

## 代码示例

**注意：此示例会用到前面几章的[`insert_begin`](../3.添加元素/README.md#头插法)和[`insert_after`](../5.任意位置插入元素/README.md#代码示例)函数**

### 处理特殊情况

#### 有两种特殊情况

1. 链表为空
2. 插入位置为第一个节点

#### 处理链表为空的情况

```c
void insert_sorted(Node **root, int value)
{
    if (*root == NULL)
    {
        insert_begin(root, value);
        return; // 退出函数
    }
}
```

`*root == NULL` 表示链表为空

#### 处理插入位置为第一个节点的情况

```c
void insert_sorted(Node **root, int value)
{
    if (*root == NULL || value <= (*root)->x)
    {
        insert_begin(root, value);
        return; // 退出函数
    }
}
```

`value <= (*root)->x` 表示 `value` 小于等于 头节点的值

### 遍历链表，找到插入位置并插入

#### 遍历链表

```c
void insert_sorted(Node **root, int value)
{
    if (*root == NULL || value <= (*root)->x)
    {
        insert_begin(root, value);
        return; // 退出函数
    }

    Node *curr = *root;
    while(curr->next != NULL)
    {
        curr = curr->next;
    }
}
```

#### 找到插入位置并插入

```c
void insert_sorted(Node **root, int value)
{
    if (*root == NULL || value <= (*root)->x)
    {
        insert_begin(root, value);
        return; // 退出函数
    }

    Node *curr = *root;
    while(curr->next != NULL)
    {
        if (value <= curr->next->x) // 找到插入位置
        {
            insert_after(curr, value); // 插入节点
            return; // 退出函数
        }
        curr = curr->next;
    }
}
```

`if (value <= curr->next->x)` 表示 `value` 小于等于 下一个节点的值

#### 这里出现的问题

如果插入位置在最后一个节点，那么 `curr->next!= NULL` 为`false`，循环不会执行，导致节点无法插入

#### 解决方案——循环外插入节点

```c
void insert_sorted(Node **root, int value)
{
    if (*root == NULL || value <= (*root)->x)
    {
        insert_begin(root, value);
        return; // 退出函数
    }

    Node *curr = *root;
    while(curr->next != NULL)
    {
        if (value <= curr->next->x) // 找到插入位置
        {
            insert_after(curr, value); // 插入节点
            return; // 退出函数
        }
        curr = curr->next;
    }
    insert_after(curr, value); // 插入节点
}
```

#### 优化代码

由于此代码循环外和循环内都有`insert_after`函数，所以可以将`insert_after`函数放在循环外

```c
void insert_sorted(Node **root, int value)
{
    if (*root == NULL || value <= (*root)->x)
    {
        insert_begin(root, value);
        return; // 退出函数
    }

    Node *curr = *root;
    while(curr->next != NULL)
    {
        if (value <= curr->next->x) // 找到插入位置
        {
            break; // 退出循环
        }
        curr = curr->next;
    }
    insert_after(curr, value);
}
```

[源代码](链表排序.c#L38)