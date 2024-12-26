#include <stdio.h>

void func()
{
    printf("Hello world!\n");
}

static void sfunc()
{
    printf("This is a static function!\n");
}


// 静态函数的用处

// 1. 隐藏函数的实现细节

static int add(int a, int b)
{
    return a + b;
}

void report()
{
    printf("Result = %d\n", add(1, 2));
}


// 2. 避免命名冲突

static void print()
{
    printf("Hello!\n");
}
