# 双链表遍历

## 步骤

1. 初始化指针 `curr` 指向链表的头节点
2. 循环遍历链表，直到 `curr` 指向 `null`

## 代码示例

## 向前遍历

### 初始化 `curr` 指针

```c
    Node *curr = tail;
```

### 遍历链表

```c
    Node *curr =tail;
    while () {  }
```

#### 确定循环条件

```c
    Node *curr =tail;
    while (curr != NULL)
    {
        printf("%d ",curr->x);
    }
```

#### 移动 `curr` 指针

```c
    Node *curr =tail;
    while (curr!= NULL)
    {
        printf("%d ",curr->x);
        curr = curr->next;
    }
```

### For 循环
```c
    for (Node *curr = tail; curr != NULL; curr = curr->next)
    {
        printf("%d ", curr->x);
    }
```

## 向后遍历

```c
    Node *curr =head;
    while (curr!= NULL)
    {
        printf("%d ",curr->x);
        curr = curr->prev;
    }
```

### For 循环

```c
    for (Node *curr = head; curr!= NULL; curr = curr->prev)
    {
        printf("%d ", curr->x);
    }
```

[源代码](双链表遍历.c#L41)