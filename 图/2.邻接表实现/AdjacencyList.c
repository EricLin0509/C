# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

#define MAX_NODES 100 // 最大节点数

typedef struct Edge { // 边
    int target; // 目标顶点索引
    struct Edge *next; // 下一个边
} Edge;

typedef struct Node { // 节点
    int data; // 节点的值
    bool visited; // 节点是否被访问过
    struct Edge *edges; // 节点的边
} Node;

Node graph[MAX_NODES]; // 图的数组，每个元素是一个节点

void init_nodes()
{
    for (int i = 0; i < MAX_NODES; i++)
    {
        graph[i].data = i; // 节点的值
        graph[i].visited = false; // 节点是否被访问过
        graph[i].edges = NULL; // 节点的边
    }
}

void add_edge(Node *node, int target)
{
    Edge *new_edge = malloc(sizeof(Edge)); // 生成新的边
    if (new_edge == NULL) return; // 内存分配失败，返回NULL
    new_edge->target = target; // 目标顶点索引
    new_edge->next = node->edges; // 原先的边作为新边的下一个边

    node->edges = new_edge; // 将新的边添加到节点的边链表中
}

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

void print_graph()
{
    for (int i = 0; i < MAX_NODES; i++)
    {
        Edge *edge = graph[i].edges; // 节点的边
        while (edge!= NULL) // 遍历节点的边链表
        {
            printf("%d -> %d\n", i, edge->target); // 输出边
            edge = edge->next; // 下一个边
        }
    }
}

int main(int argc, const char *argv[]) {
    init_nodes(); // 初始化节点
    add_edge(&graph[0], 1); // 添加边
    add_edge(&graph[0], 2); // 添加边
    add_edge(&graph[1], 3); // 添加边
    add_edge(&graph[1], 4); // 添加边
    add_edge(&graph[2], 5); // 添加边
    add_edge(&graph[2], 6); // 添加边
    print_graph(); // 打印图
    destroy_graph(); // 销毁图
    return 0;
}