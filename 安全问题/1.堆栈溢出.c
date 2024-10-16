// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

int sum (int a[], int length, int i)
{
    if (i == length)
    {
        return 0; // 递归出口
    }
    else
    {
        return a[i] + sum(a, length, i+1); // 递归调用
    }
    
}

int f2(int a, int b)
{
    printf("a = %d, b = %d\n", a, b);
}

int f1(int a, int b)
{
    f2(a, b);
}

int function1()
{
    int big_array[100000000];
}
int function2()
{
    int big_array[100000000];
    function1();
}

int main(int argc, char const *argv[]) {

// 堆栈是一种数据结构，它是一种后进先出的数据结构
// 堆栈里面的元素叫栈帧


f1(1, 2);
/*
栈调用过程：

                              f2
                              |
                f1           f1         f1
                |             |            |
main -> main -> main-> main-> main
*/


// 堆栈溢出
int a[1000000];
int length = 1000000;

for (int i = 0; i < length; i++)
{
    a[i] = 1;
}

int result = sum(a, length, 0); // 会导致堆栈溢出

printf("result = %d\n", result);
/*
堆栈溢出是指程序在运行时，由于栈空间不足，导致程序无法正常执行的情况
*/

function2(); // 同样会导致堆栈溢出

/*
堆栈溢出的原因：
1. 递归调用的层数过多
2. 函数调用的层数过多
3. 函数调用的参数过多
4. 函数调用的返回值过多
5. 函数调用的局部变量过多
6. 函数调用的局部变量过大
7. 函数调用的局部变量过大
8. 函数调用的局部变量过大
*/

return 0;

}