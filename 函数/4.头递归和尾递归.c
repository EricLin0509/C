// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

// 头递归
int sum_head(int n, int result)
{
    if (n > 0)
    {
        return sum_head(n - 1, result + n); // 递归情况，累加结果
    }
    else
    {
        return result; // 基本情况，返回累加结果
    }
}
/*
头递归是一种递归函数的形式，它的特点是在递归调用之前执行操作
*/


// 尾递归
int sum_tail(int n, int result)
{
    if (n == 0)
    {
        return result; // 基本情况，返回累加结果
    }
    else
    {
        return sum_tail(n - 1, result + n); // 递归情况，累加结果
    }
}
/*
尾递归是一种递归函数的形式，它的特点是在递归调用之后执行操作
*/


int main(int argc, const char * argv[]) {

    printf("sum_head = %d\n", sum_head(10, 0)); // 调用头递归函数，计算1到10的和

    printf("sum_tail = %d\n", sum_tail(10, 0)); // 调用尾递归函数，计算1到10的和

    return 0;
}
