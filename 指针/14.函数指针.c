// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>

void function_pointer(char *str)
{

}

int Add(int x,int y)
{
    return x+y;
}

void (*signal(int, void(*)(int)))(int);
/*
signal 和 () 先结合，说明 signal 是函数名
signal 函数的第一个参数类型是 int，第二个参数的类型是函数指针
该函数指针，指向一个参数为 int，返回类型是 void 的函数
signal 函数的返回类型也是一个函数指针
该函数指针，指向一个参数为 int，返回类型是 void 的函数
signal 是一个函数声明
*/

int main(int argc, const char * argv[]) {

int a = 10;
int *pa = &a;

int arr[10] = {1,2,3,4,5,6,7,8,9,10};
int (*parr)[10] = &arr; // 取出数组的地址
printf("%d\n\n",(*parr)[5]); // 输出6

// 函数指针 - 存放函数地址的指针
// &函数名 取得的就是函数的地址
// 函数名 == &函数名
printf("%zu\n",Add);
printf("%zu\n\n",&Add); // 两者相同

int (*pf)(int, int) = &Add; // pf 就是一个函数指针变量
/*
int 说明函数返回类型为 int
(*pf) 说明是个指针
(int, int) Add 这个函数对应的传参类型
*/
int (*pf2)(int, int) = Add; // Add == pf

void (*pt)(char *) = &function_pointer;

int result = (*pf)(3, 5); // 此处的 * 没意义
int result2 = pf(3, 5);
// int result3 = *pf(3, 5); // ❌ 此处相当于对返回值进行解引用
printf("result: %d\n",result);
printf("result2: %d\n",result2);

// (*(void(*)())0)();
// 该函数无参，返回类型是 void
/*
void(*)() 函数指针类型
(void(*)())0 对0进行强制转换，被解释为一个函数地址
*(void(*)())0 对0地址进行了解引用
(*(void(*)())0)() 调用0地址处的函数
*/

return 0;

}

