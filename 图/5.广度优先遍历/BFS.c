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

Node graph[6];  // 顶点数组

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

void bfs(Node *root)
{
    Node *queue[100]; // 队列
    int front = 0; // 队列的头
    int rear = 0; // 队列的尾

    queue[rear++] = root; // 将根节点入队

    while (rear > front) // 直到队列为空
    {
        Node *node = queue[front++]; // 取出队头元素

        printf("%c ", node->data); // 打印节点的数据

        for (Edge *edge = node->edges; edge != NULL; edge = edge->next) // 遍历节点的相邻节点
        {
            Node *target = &graph[edge->target]; // 相邻节点
            if (!target->visited) // 如果相邻节点没有被访问过
            {
                target->visited = true; // 标记相邻节点为已访问
                queue[rear++] = target; // 将相邻节点入队
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
    
    printf("从A开始BFS遍历: ");
    bfs(&graph[0]);  // A C B E D F

    destroy_graph(graph); // 释放内存
    return 0;
}