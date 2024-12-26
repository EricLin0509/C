#include <stdio.h>

// typedef 关键字
// 1. 给类型起别名
// 2. 简化复杂的类型声明

typedef unsigned long long UINT64; // 给 unsigned long long 起别名 UINT64

typedef struct Point {
    double x, y;
} Point;


// typedef 原理
typedef struct Node Node;
/*
先定义一个 'struct Node' 类型
然后 'typedef' 将 'struct Node' 改名为 'Node'
*/

int main(int argc, const char *argv[]) {

    UINT64 a = 14; // 使用别名
    printf("%llu\n", a);

    Point p; // 简化复杂的类型声明
    p.x = 10.5;
    p.y = 20.5;
    printf("%.2lf %.2lf\n", p.x, p.y);

    return 0;
}