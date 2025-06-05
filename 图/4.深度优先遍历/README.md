# 深度优先遍历

## 简介

深度优先遍历是一种用于遍历或搜索树或图的算法。在这个算法中，算法从一个根节点开始，然后探索尽可能深的分支，直到到达树的底部，然后回溯到上一个分支并继续探索。这个过程一直持续到遍历完整个树或图

## 步骤

以下面的图为例

![Example](imgs/Example.png)

由于图不存在根节点，所以我们可以从任何一个节点开始遍历。这里我们从节点 `A` 开始遍历

![step1](imgs/step1.png)

由于 `A` 有两个相邻的节点 `B` 和 `C`，这里我们选择 `C` 作为下一个节点

![step2](imgs/step2.png)

从 `C` 开始往下，直到不能再往后遍历

![step3](imgs/step3.png)

由于 `E` 没有相邻的节点，所以我们回到 `B` 节点

![step4](imgs/step4.png)

从 `B` 开始往下，直到不能再往后遍历

![step5](imgs/step5.png)

由于 `D`的相邻节点都已经被遍历过了，所以结束遍历

可以发现，`F` 节点并没有被遍历过，这是因为 `F` 节点是一个孤立的节点，没有相邻的节点

## 实现

由于每个节点都是先进后出，所以我们可以使用**栈**来实现深度优先遍历

```c
typedef struct Edge { // 边
    int target; // 目标顶点索引
    struct Edge *next; // 下一个边
} Edge;

typedef struct Node { // 节点
    int data; // 节点的值
    bool visited; // 节点是否被访问过
    struct Edge *edges; // 节点的边
} Node;

void dfs(Node *root);
```

### 设置栈

```c
void dfs(Node *root)
{
    Node *stack[100]; // 栈
    int size = 0; // 栈的大小
}
```

### 将根节点入栈

将根节点入栈，用于后续的遍历

```c
void dfs(Node *root)
{
    Node *stack[100]; // 栈
    int size = 0; // 栈的大小

    stack[size++] = root; // 将根节点入栈
}
```

### 遍历

直到栈为空

```c
void dfs(Node *root)
{
    Node *stack[100]; // 栈
    int size = 0; // 栈的大小

    stack[size++] = root; // 将根节点入栈

    while (size > 0) {    } // 直到栈为空
}
```

### 取出栈顶元素

```c
void dfs(Node *root)
{
    Node *stack[100]; // 栈
    int size = 0; // 栈的大小

    stack[size++] = root; // 将根节点入栈

    while (size > 0) // 直到栈为空
    {
        Node *node = stack[--size]; // 取出栈顶元素
        printf("%c ", node->data); // 打印节点的数据
    }
    printf("\n");
}
```

### 遍历节点的相邻节点

```c
void dfs(Node *root)
{
    Node *stack[100]; // 栈
    int size = 0; // 栈的大小

    stack[size++] = root; // 将根节点入栈

    while (size > 0) // 直到栈为空
    {
        Node *node = stack[--size]; // 取出栈顶元素
        printf("%c ", node->data); // 打印节点的数据

        for (Node *next = node->edges; next != NULL; next = next->next) // 遍历节点的相邻节点
        {
            stack[size++] = next; // 将相邻节点入栈
        }
    }
    printf("\n");
}
```

### 去除重复的节点

可能会出现重复的节点，那可以使用标记来解决

```c
typedef struct Node {
    char data;
    struct Node *next;
    bool visited; // 是否被访问过
} Node; // 使用领接表来表示图
```

```c
void dfs(Node *root)
{
    Node *stack[100]; // 栈
    int size = 0; // 栈的大小

    stack[size++] = root; // 将根节点入栈

    while (size > 0) // 直到栈为空
    {
        Node *node = stack[--size]; // 取出栈顶元素
        printf("%c ", node->data); // 打印节点的数据

        for (Node *next = node->edges; next != NULL; next = next->next) // 遍历节点的相邻节点
        {
            Node *target = &graph[edge->target]; // 相邻节点
            if (!target->visited) // 如果相邻节点没有被访问过
            {
                next->visited = true; // 标记相邻节点为已访问
                stack[size++] = next; // 将相邻节点入栈
            }
        }
    }
    printf("\n");
}
```