// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>
int main(int argc, const char * argv[]) {

// 数组名是数组的首地址 这是一个常量
int arr[10] = {1,2,3,4,5,6,7,8,9,10};
printf("%p\n",arr);
printf("%p\n",&arr[0]); // 输出结果一样
// p=arr [数据类型 *] 变量名
// 1. 指向数组的指针 当操作指针的时候，间接操作了数组
int * p = arr;
for (int i = 0; i < 10; i++)
{
    printf("%d\n",p[i]);
}
putchar('\n');

for (int i = 0; i < 10; i++)
{
    printf("%d\n",*(p + i)); // *(p + i) 内存变了1*sizeof(int)
}



// 指针的降级操作
*p = 100;
p[5] = 300;

*(p + 1) = 200; // 在 p 的地址上向后移一位

p++; // 改变 p 的地址
*p = 200; // p 的地址已经向后移一位了
p[2] = 300;
arr[2] = 400;

// 数组下标越界
// p[10] = 300;
// p -= 3;

for (int i = 0; i < 9; i++)
{
    printf("%d\n",*(p + i));
}

// arr[2] <==> *(arr + 2) <==> *(p + 2) <==> *(2 + arr)
// 2[arr] <==> *(arr + 2)
// [] 是一个操作符，2和 arr 是两个操作数
printf("%d\n",2[arr]); // 400


// 指针数组
int arr[10]; // 整形数组
char ch[5]; // 字符数组

// 指针数组 - 存放指针的数组
int *parr[5]; // 整形指针数组
return 0;

}