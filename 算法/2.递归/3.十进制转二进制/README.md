# 十进制转二进制

## 题目描述

给定一个十进制数M，以及需要转换的进制数N。将十进制数M转化为N进制数

条件:

- M为正整数

示例: 

- tobinary(10) => 1010
- tobinary(15) => 1111

## 解题思路

使用数学方法，不断除以进制数，直到商为0，将余数倒序排列即可

```c
typedef struct Node {
    int data;
    struct Node *next;
} Node; // 定义链表节点，实现栈

int tobinary(int m, Node *stack)
```

首先确定基准条件，即商为0时，返回结果

```c
Node* tobinary(int m, Node *stack)
{
    if (m == 0) return stack;
}
```

然后计算结果的每一位，即余数

```c
Node* tobinary(int m, Node *stack)
{
    if (m == 0) return stack;
    Node *node = malloc(sizeof(Node));
    node->data = m % 2;
    node->next = stack;
}
```

最后，确定递归条件

即哪个最小单元可以向目标前进

这里是m除以进制数，即m/2，node是根节点

```c
Node* tobinary(int m, Node *stack)
{
    if (m == 0) return stack;
    Node *node = malloc(sizeof(Node));
    node->data = m % 2;
    node->next = stack;
    return tobinary(m / 2, node);
}
```