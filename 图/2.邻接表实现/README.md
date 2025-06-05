# 领接表实现

我们需要两个结构体 `Node` 和 `Edge`

- `Node` —— 表示节点，包含三个属性：
   - `data` —— 节点的值
   - `visited` —— 节点是否被访问过，用于图的遍历 (可选)
   - `edges` —— 节点的边，是一个链表，链表的每个节点表示一个边，边的值表示边的终点

- `Edge` —— 表示边，包含两个属性：
   - `target` —— 目标顶点索引，表示边的终点
   - `next` —— 下一个边，用于链表的遍历


```c
typedef struct Edge { // 边
    int target; // 目标顶点索引
    struct Edge *next; // 下一个边
} Edge;

typedef struct Node { // 节点
    int data; // 节点的值，可以是任意类型，这里用 int 表示
    bool visited; // 节点是否被访问过 (可选)
    struct Edge *edges; // 节点的边
} Node;
```

## 初始化图

图的初始化需要一个数组，数组的每个元素是一个节点

这里使用一个全局变量 `graph` 来表示图

> **注意：如果不是全局变量，那么需要在函数中传递一个指向图的指针**

```c
#define MAX_NODES 100 // 最大节点数

Node graph[MAX_NODES]; // 图的数组，每个元素是一个节点
```

## 初始化节点

节点的初始化需要一个值，一个边，一个是否被访问过

边初始化为 `NULL`，因为节点还没有边

```c
void init_nodes()
{
    for (int i = 0; i < MAX_NODES; i++)
    {
        graph[i].data = i; // 节点的值
        graph[i].visited = false; // 节点是否被访问过
        graph[i].edges = NULL; // 节点的边
    }
}
```

## 添加边

```c
void add_edge(Node *node, int target);
```

- `node` —— 节点
- `target` —— 目标顶点索引，表示边的终点

### 生成新的边

需要把**原先的边作为新边的下一个边**，然后将新的边作为节点的边链表的头节点

简单来说，就是**链表的头插法**

```c
void add_edge(Node *node, int target)
{
    Edge *new_edge = malloc(sizeof(Edge)); // 生成新的边
    if (new_edge == NULL) return; // 内存分配失败，返回NULL
    new_edge->target = target; // 目标顶点索引
    new_edge->next = node->edges; // 原先的边作为新边的下一个边
}
```

### 将新的边添加到节点的边链表中

```c
void add_edge(Node *node, int target)
{
    Edge *new_edge = malloc(sizeof(Edge)); // 生成新的边
    new_edge->target = target; // 目标顶点索引
    new_edge->next = node->edges; // 原先的边作为新边的下一个边

    node->edges = new_edge; // 将新的边添加到节点的边链表中
}
```

## 销毁图

```c
void destroy_graph();
```

### 遍历节点

```c
void destroy_graph()
{
    for (int i = 0; i < MAX_NODES; i++) {   } // 遍历节点
}
```

### 遍历节点的边链表

```c
void destroy_graph()
{
    for (int i = 0; i < MAX_NODES; i++)
    {
        Edge *edge = graph[i].edges; // 节点的边
        while (edge != NULL) {    } // 遍历节点的边链表
    }
}
```

### 释放边

跟链表的释放一样，**先保存下一个边，然后释放当前边**

```c
void destroy_graph()
{
    for (int i = 0; i < MAX_NODES; i++)
    {
        Edge *edge = graph[i].edges; // 节点的边
        while (edge != NULL) // 遍历节点的边链表
        {
            Edge *next = edge->next; // 保存下一个边
            free(edge); // 释放当前边
            edge = next; // 下一个边
        }
    }
}
```

**由于这里图的节点是一个数组，所以不需要释放节点**

## 输出图

```c
void print_graph();
```

### 遍历节点

```c
void print_graph()
{
    for (int i = 0; i < MAX_NODES; i++) {    } // 遍历节点
}
```

### 遍历节点的边链表

```c
void print_graph()
{
    for (int i = 0; i < MAX_NODES; i++)
    {
        Edge *edge = graph[i].edges; // 节点的边
        while (edge!= NULL) {    } // 遍历节点的边链表
    }
}
```

### 输出边

```c
void print_graph()
{
    for (int i = 0; i < MAX_NODES; i++)
    {
        Edge *edge = graph[i].edges; // 节点的边
        while (edge != NULL) // 遍历节点的边链表
        {
            printf("%d -> %d\n", i, edge->target); // 输出边
            edge = edge->next; // 下一个边
        }
    }
}
```