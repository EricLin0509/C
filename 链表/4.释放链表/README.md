# 释放链表

## 使用函数

### 删除节点

```c
void deallocate(Node **root)
{
    free(*root);
}
```

#### 这里出现的问题

`free(*root)` 只能释放掉头节点，不能释放链表中其他节点，且无法找到其他节点的地址

#### 解决方案——遍历链表
```c
void deallocate(Node **root)
{
    Node *curr = *root;

    while(curr != NULL) // 遍历链表
    {
        curr = curr->next;
        free(curr);
    }
}
```

#### 这里出现的问题

`free(curr)` 只能释放当前节点，无法找到其他节点的地址，所以无法释放链表中其他节点

#### 解决方案——保存当前节点的地址
```c
void deallocate(Node **root)
{
    Node *curr = *root;

    while(curr != NULL) // 遍历链表
    {
        Node *temp = curr; // 保存当前节点的地址
        curr = curr->next;
        free(temp); // 释放当前节点
    }
}
```

由于 `curr` 指向下一个节点，所以后面的节点地址依旧存在，所以可以继续遍历链表

### 重置头节点

```c
void deallocate(Node **root)
{
    Node *curr = *root;

    while(curr != NULL) // 遍历链表
    {
        Node *temp = curr; // 保存当前节点的地址
        curr = curr->next;
        free(temp); // 释放当前节点
    }

    *root = NULL; // 重置头节点
}
```

[源代码](释放链表.c)

## 使用递归

```c
void deallocate(Node **root)
{
    if (*root == NULL) // 如果链表为空，直接返回
    {
        return;
    }
    
    deallocate(&(*root)->next); // 递归释放下一个节点

    free(*root); // 释放当前节点
    *root = NULL; // 重置当前节点
}
```