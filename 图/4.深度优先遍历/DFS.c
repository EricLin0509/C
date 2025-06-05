#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Edge { // 边
    int target; // 目标顶点索引
    struct Edge *next; // 下一个边
} Edge;

typedef struct Node { // 节点
    char data; // 节点的值
    bool visited; // 节点是否被访问过
    struct Edge *edges; // 节点的边
} Node;

void add_edge(Node *node, int target)
{
    Edge *new_edge = malloc(sizeof(Edge)); // 生成新的边
    if (new_edge == NULL) return; // 内存分配失败，返回NULL
    new_edge->target = target; // 目标顶点索引
    new_edge->next = node->edges; // 原先的边作为新边的下一个边

    node->edges = new_edge; // 将新的边添加到节点的边链表中
}

void destroy_graph(Node *graph)
{
    for (int i = 0; i < 6; i++)
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

Node graph[6]; // 图的节点数组，每个元素是一个节点

void dfs(Node *root)
{
    Node *stack[100]; // 栈
    int size = 0; // 栈的大小

    stack[size++] = root; // 将根节点入栈

    while (size > 0) // 直到栈为空
    {
        Node *node = stack[--size]; // 取出栈顶元素

        printf("%c ", node->data); // 打印节点的数据

        for (Edge *edge = node->edges; edge != NULL; edge = edge->next) // 遍历节点的边
        {
            Node *target = &graph[edge->target]; // 目标节点
            if (!target->visited) // 如果目标节点没有被访问过
            {
                target->visited = true; // 标记目标节点为已访问
                stack[size++] = target; // 将目标节点入栈
            }
        }
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // 初始化顶点
    for (int i = 0; i < 6; i++) {
        graph[i].data = 'A' + i;
        graph[i].visited = false;
        graph[i].edges = NULL;
    }

    // 添加边关系
    add_edge(&graph[0], 1);  // A->B
    add_edge(&graph[0], 2);  // A->C
    add_edge(&graph[1], 3);  // B->D
    add_edge(&graph[2], 4);  // C->E
    add_edge(&graph[3], 5);  // D->F
    
    printf("从A开始DFS遍历: ");
    dfs(&graph[0]);  // A B D F C E

    destroy_graph(graph);  // 释放内存
    return 0;
}