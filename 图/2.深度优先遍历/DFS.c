#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char data;
    struct Node *next;
    bool visited;
} Node; // 使用领接表来表示图

void dfs(Node *root)
{
    Node *stack[100]; // 栈
    int size = 0; // 栈的大小

    stack[size++] = root; // 将根节点入栈

    while (size > 0) // 直到栈为空
    {
        Node *node = stack[--size]; // 取出栈顶元素

        if (node->visited) continue; // 如果已经被访问过，跳过
        node->visited = true; // 标记为已访问 

        printf("%c ", node->data); // 打印节点的数据

        Node *temp[100]; // 临时栈
        int count = 0; // 临时栈的大小

        for (Node *next = node->next; next!= NULL; next = next->next) // 遍历节点的相邻节点
        {
            temp[count++] = next; // 将相邻节点入栈
        }

        for (int i = count - 1; i >= 0; i--) // 反转临时栈
        {
            stack[size++] = temp[i];
        }
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    Node *graph[6]; // 图的节点数组
    // 初始化图的节点
    for (int i = 0; i < 6; i++)
    {
        graph[i] = (Node *)malloc(sizeof(Node));
        graph[i]->data = 'A' + i; // 分别用A、B、C、D、E、F
        graph[i]->next = NULL;
        graph[i]->visited = false;
    }

    // 构建图的边
    graph[0]->next = graph[1];
    graph[0]->next->next = graph[2]; // A->B, A->C
    graph[1]->next = graph[3]; // B->D
    graph[3]->next = graph[2]; // D->C
    graph[2]->next = graph[4]; // C->E
    graph[4]->next = graph[5]; // E->F

    dfs(graph[0]); // 从节点0开始遍历
    return 0;
}