// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>
int main(int argc, const char * argv[]) {

// 这种方式不安全，可以通过指针修改
// 1. 通过指针修改 const 修饰的常量
const int a = 10;
int * p = &a;
*p = 100;
printf("%d\n",a);
printf("%d\n",*p);


// 2.如果 const 修饰 'int *' 类型不能改变指针变量指向的内存地址的值
// 但是可以改变指针指向的地址
int  b = 10;
int c = 20;
const int * p2;
p2 = &b;
p2 = &c;
// *p2 = 100; ❌
printf("%d\n",*p2);


// 3. const 修饰指针变量能改变指针变量指向地址的值
// 但是不能改变指针指向的地址
int * const  p3 = &b;
// p3 = &c; ❌
*p3 = 100;
printf("%d\n",*p3);


// 4. const 修饰指针类型也修饰指针变量
// 那么不能改变指针指向的地址也不能修改指针指向的值
int d = 10;
int e = 20;
const int * const p4 = &d;
// p4 =&e; ❌
// *p4 = 100; ❌

return 0;

}