#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Edge {
    int target;
    struct Edge *next;
} Edge;

typedef struct Node {
    char data;
    bool visited;
    struct Edge *edges;
} Node;

void add_edge(Node *node, int target)
{
    Edge *new_edge = malloc(sizeof(Edge));
    new_edge->target = target;
    new_edge->next = node->edges;
    node->edges = new_edge;
}

void destroy_graph(Node *root)
{
    for (int i = 0; i < 6; i++)
    {
        Edge *edge = root[i].edges; // 节点的边
        while (edge != NULL) // 遍历节点的边链表
        {
            Edge *next = edge->next; // 保存下一个边
            free(edge); // 释放当前边
            edge = next; // 下一个边
        }
    }
}

bool has_path(Node *start, Node *end)
{
    if (start == end) return true; // 相同节点

    Node *stack[100]; // 栈
    int size = 0; // 栈大小

    stack[size++] = start; // 将 start 入栈

    while (size > 0) // 遍历栈
    {
        Node *node = stack[--size]; // 取出栈顶元素

        for (Edge *edge = node->edges; edge != NULL; edge = edge->next) // 遍历节点的边
        {
            Node *target = &start[edge->target]; // 目标节点

            if (target == end) return true; // 找到目标节点

            if (!target->visited) // 如果目标节点未被访问
            {
                target->visited = true; // 标记为已访问
                stack[size++] = target; // 将目标节点入栈
            }
        }
    }
    return false; // 未找到目标节点
}

int main(int argc, const char *argv[]) {
    Node nodes[6];
    for (int i = 0; i < 6; i++) // 初始化节点
    {
        nodes[i].data = 'f' + i;
        nodes[i].visited = false;
        nodes[i].edges = NULL;
    }

    add_edge(&nodes[0], 1); // f -> g
    add_edge(&nodes[0], 3); // f -> i
    add_edge(&nodes[1], 2); // g -> h
    add_edge(&nodes[3], 1); // i -> g
    add_edge(&nodes[4], 3); // j -> i
    add_edge(&nodes[3], 5); // i -> k

    Node *start = &nodes[0]; // f
    Node *end = &nodes[5]; // k

    printf("%s\n", has_path(start, end) ? "True" : "False"); // True
    
    start = &nodes[0]; // f
    end = &nodes[4]; // j

    printf("%s\n", has_path(start, end)? "True" : "False"); // False

    destroy_graph(nodes); // 释放内存
    return 0;
}