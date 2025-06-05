# 邻接矩阵实现

这里只需要一个结构体 `Graph` 来表示图

- `Graph` 结构体包含两个属性：
  - `nodesNum`：图中节点的数量
  - `edges`：邻接矩阵，用于存储图中节点之间的边

```c
typedef struct Graph {
    int nodesNum;
    int **edges;
} Graph;
```

`edges` 使用二级指针来表示，因为邻接矩阵是一个二维数组，每个元素表示两个节点之间的边

## 初始化

初始化函数 `initGraph` 用于初始化图

```c
Graph *initGraph(int nodesNum);
```

- `nodesNum`：图中节点的数量

### 初始化 `Graph` 结构体

```c
Graph *initGraph(int nodesNum)
{
    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL) return NULL; // 失败返回 NULL
    graph->nodesNum = nodesNum;
}
```

### 初始化 `edges` 数组

```c
Graph *initGraph(int nodesNum)
{
    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL) return NULL; // 失败返回 NULL
    graph->nodesNum = nodesNum;

    // 初始化 edges 数组
    graph->edges = calloc(nodesNum, sizeof(int *)); // 使用 calloc 初始化数组为 0
    if (graph->edges == NULL)
    {
        free(graph); // 释放已分配的内存
        return NULL; // 失败返回 NULL
    }
    for (int i = 0; i < nodesNum; i++) // 创建子数组
    {
        graph->edges[i] = calloc(nodesNum, sizeof(int)); // 使用 calloc 初始化数组为 0
        if (graph->edges[i] == NULL)
        {
            destroyGraph(graph); // 释放已分配的内存
            return NULL; // 失败返回 NULL
        }
    }
    return graph; // 成功返回 Graph 结构体
}
```

## 销毁

销毁顺序为：

1. 释放 `edges` 数组中的每个子数组
2. 释放 `edges` 数组
3. 释放 `Graph` 结构体

> 警告：**必须严格按照顺序释放内存**，否则会导致内存泄漏

```c
void destroyGraph(Graph *graph);
```

### 判断是否为 `NULL`

```c
void destroyGraph(Graph *graph)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回
}
```

### 遍历 `edges` 数组并释放子数组

```c
void destroyGraph(Graph *graph)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回

    for (int i = 0; i < graph->nodesNum; i++) // 遍历 edges 数组
    {
        if (graph->edges[i] != NULL) // 如果子数组不为 NULL
        {
            free(graph->edges[i]); // 释放子数组
        }
    }
}
```

### 释放 `edges` 数组

```c
void destroyGraph(Graph *graph)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回

    for (int i = 0; i < graph->nodesNum; i++) // 遍历 edges 数组
    {
        if (graph->edges[i] != NULL) // 如果子数组不为 NULL
        {
            free(graph->edges[i]); // 释放子数组
        }
    }
    free(graph->edges); // 释放 edges 数组
}
```

### 释放 `Graph` 结构体

```c
void destroyGraph(Graph *graph)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回

    for (int i = 0; i < graph->nodesNum; i++) // 遍历 edges 数组
    {
        if (graph->edges[i] != NULL) // 如果子数组不为 NULL
        {
            free(graph->edges[i]); // 释放子数组
        }
    }
    free(graph->edges); // 释放 edges 数组

    free(graph); // 释放 Graph 结构体
}
```

## 输出边

```c
void printGraph(Graph *graph);
```

### 判断是否为 `NULL`

```c
void printGraph(Graph *graph)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回
}
```

### 遍历 `edges` 数组并输出

```c
void printGraph(Graph *graph)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回

    for (int from = 0; from < graph->nodesNum; from++) // 遍历 edges 数组
    {
        for (int target = 0; target < graph->nodesNum; target++) // 遍历子数组
        {
            if (graph->edges[from][target] != 0) // 如果边存在
            {
                printf("(%d -> %d)\n", from, target); // 输出边
            }
        }
    }
}
```

## 添加边

```c
void addEdge(Graph *graph, int from, int target);
```

- `from`：边的起点
- `target`：边的终点

### 判断是否已存在边

```c
void addEdge(Graph *graph, int from, int target)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回
    if (hasEdge(graph, from, target)) return; // 如果边已存在，直接返回
}
```

### 添加边

```c
void addEdge(Graph *graph, int from, int target)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回
    if (hasEdge(graph, from, target)) return; // 如果边已存在，直接返回

    graph->edges[from][target] = 1; // 添加边
}
```

## 判断是否存在边

```c
bool hasEdge(Graph *graph, int from, int target);
```

- `from`：边的起点
- `target`：边的终点

### 判断是否为 `NULL`

```c
bool hasEdge(Graph *graph, int from, int target)
{
    if (graph == NULL) return false; // 如果 graph 为 NULL，返回 false
}
```

### 判断是否存在边
```c
bool hasEdge(Graph *graph, int from, int target)
{
    if (graph == NULL) return false; // 如果 graph 为 NULL，返回 false

    return graph->edges[from][target] != 0; // 返回边是否存在
}
```