# 链表遍历

## 数组遍历

```c
    int arr[5] = {1,2,3,4,5};

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", arr[i]);
    }
```

## 链表遍历

### 遍历方式

1. 创建指针指向某个节点
2. 执行循环体
3. 指针指向下一个节点的地址
4. 由于链表以 NULL 结尾，所以遍历到 NULL 结束


### 代码示例

```c
    struct Node root = {1, NULL};
    struct Node *curr = &root; // 指针指向第一个节点

    while(curr != NULL) // 遍历到 NULL 结束
    {
        printf("%d\n",curr->x);
        curr = curr->next; // 指向下一个节点
    }
```

**或者**

```c
    struct Node root = {1, NULL};
    struct Node *curr = &root; // 指针指向第一个节点

    for (curr = &root; curr != NULL; curr = curr->next)
    {
        printf("%d\n",curr->x);
    }
```

[源代码](链表遍历.c#L22)

## 两者遍历比较

| 数组 | 链表 |
| :----: | :----: |
| int i = 0 | struct node *curr = &root; |
| i < n | curr != NULL |
| i++ | curr = curr->next; |

