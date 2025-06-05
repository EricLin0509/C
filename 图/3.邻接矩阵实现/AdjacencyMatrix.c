#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Graph {
    int nodesNum;
    int **edges;
} Graph;

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

Graph *initGraph(int nodesNum)
{
    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL) return NULL; // 失败返回 NULL
    graph->nodesNum = nodesNum;

    // 初始化 edges 数组
    graph->edges = calloc(nodesNum, sizeof(int *)); // 使用 calloc 初始化数组为 0
    if (graph->edges == NULL) return NULL; // 失败返回 NULL
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

bool hasEdge(Graph *graph, int from, int target)
{
    if (graph == NULL) return false; // 如果 graph 为 NULL，返回 false

    return graph->edges[from][target]; // 返回边是否存在
}

void addEdge(Graph *graph, int from, int target)
{
    if (graph == NULL) return; // 如果 graph 为 NULL，直接返回
    if (hasEdge(graph, from, target)) return; // 如果边已存在，直接返回

    graph->edges[from][target] = 1; // 添加边
}

int main(int argc, const char *argv[]) {
    Graph *graph = initGraph(5); // 创建图
    if (graph == NULL) return 1; // 如果创建失败，返回 1
    addEdge(graph, 0, 1); // 添加边
    addEdge(graph, 0, 2); // 添加边
    addEdge(graph, 1, 3); // 添加边
    addEdge(graph, 2, 4); // 添加边
    printGraph(graph); // 输出图
    destroyGraph(graph); // 释放图
    return 0;
}