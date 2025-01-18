// Copyright (C) 2024 EricLin
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
int a = 10;
int b = 20;
int c = 30;
int *parr[3] = {&a,&b,&c}; // 整形指针数组

for (int i = 0; i < 3; i++)
{
    printf("%d ",*(parr[i]));
}
putchar('\n');

int d[5] = {1,2,3,4,5};
int e[5] = {6,7,8,9,10};
int f[5] = {11,12,13,14,15};

int *arr2[3] = {d,e,f};

for (int i = 0; i < 3; i++)
{
    for (int j = 0; j < 5; j++)
    {
        printf("%d\n",*(arr2[i]+j)); 
        // printf("%d\n",arr2[i][j]);
        // 虽然这种长得像二维数组，但是这个数组里面的内存是不连续的
    }
    
}


// 数组指针
int arr3[10] = {1,2,3,4,5};
int (*parr2)[10] = &arr3; // 取出的是数组的地址
// parr2 就是一个数组指针

int *p1 = arr;
int (*p2)[10] = &arr;

printf("%zu\n",p1);
printf("%zu\n",p1+1);

printf("%zu\n",p2);
printf("%zu\n",p2+1);
// 详情可以看注意事项——array[] 和 &array[] 的区别

double *g[5]; // 指针数组
double *(*pd)[5] = &g; // pd 就是一个数组指针

int array[5]; // 一个整形数组
int *parray[10]; // 一个整形指针数组
int (*parray2)[10]; // 一个数组指针，该指针能够指向一个数组，数组10个元素，每个元素类型是 int
int (*parray3[10])[5]; // 一个存储数组指针的数组，该数组能够存放10个数组指针，每个数组指针能够指向一个数组，数组5个元素，每个元素是 int 类型

return 0;

}