// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>

/*
函数递归调用是一种编程技巧，它允许函数调用自身来解决问题

递归函数包含两个部分：
    1. 基本情况（Base Case）：这是递归函数停止调用自身的条件
    2. 递归情况（Recursive Case）：这是函数调用自身的条件
*/

void space(int n, int size)
{
    if (n < size) // 用于控制递归函数的执行次数，防止死循环
    {
        printf("  ");
        space(n+1, size); // 函数调用自身，实现递归
    }
    
}

void star(int n, int size)
{
    if (n < size)
    {
        printf("* ");
        star(n+1, size); // 函数调用自身，实现递归
    }
    
}

int sum(int n)
{
    if (n == 0)
    {
        return 1; 
    }
    else
    {
        return n * sum(n-1); // 函数调用自身，实现递归
    }
}
 
void loop(int n);

int main(int argc, const char * argv[]) {

    int size =0;
    scanf("%d", &size);

// 非递归实现
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size-i; j++)
        {
            printf("  ");
        }
        for (int k = 0; k < (2 * i)+1; k++)
        {
            printf("* ");
        }

        printf("\n"); 
    }
    puts("\n");


// 递归实现
    for (int i = 0; i < size; i++)
    {
        space(0, size-i);
        star(0, (2 * i)+1);
        printf("\n");
    }
    puts("\n");

    printf("%d\n", sum(size)); // 递归实现阶乘

    return 0;
}

void loop(int n)
{
    loop(n); // 会导致死循环，造成堆栈溢出，因为没有终止条件
}