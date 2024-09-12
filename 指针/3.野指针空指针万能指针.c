// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>
int main(int argc, const char * argv[]) {

/*  野指针
int * p;
// 0-255 都是系统保留的，不可以读也不可以写
// 野指针是指向一个未知的内存空间，可能在读写的时候出现错误

p = 100; // 指向内存编号为100的内存地址

*p = 100; // 改变100这块内存空间里的数据
printf("%d\n",*p);
*/


/* 空指针
// 空指针就是指向内存编号为0的空间
// 一般情况 NULL 用作程序条件判断
int * p = NULL;
*p = 100;
printf("%d\n",*p); // 输出 segmentation fault
*/

/*
int * p = NULL;

if (p != NULL) // 用作程序条件判断
{
    // free();
}
*/
// 操作空指针会使程序崩溃


// 万能指针
int a = 10;
// int * p  =&a;
void * p =&a; // void 指针可以指向任何一个指针类型
*(int *)p = 100; // 需要指定指针类型
printf("%d\n",a);
printf("%d\n",*(int *)p);
putchar('\n');

int arr[10] = {0};
void * ap = arr;
*(int *)ap = 100; // 改变 arr[0] 的值
*((int *)ap+1) = 200; // 改变 arr[1] 的值
// *((int *)p+1) 中 +1 表示加一个 'int *' 类型大小

for (int i = 0; i < 10; i++)
{
    printf("%d\n",arr[i]);
}


return 0;

}
/*
如何避免野指针
1. 指针初始化    int * p = NULL;
2. 小心指针越界
3. 指针指向空间释放即设置NULL
4. 指针使用之前检查有效性   if (p != NULL)
*/