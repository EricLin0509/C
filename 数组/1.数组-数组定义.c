// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#define LENGTH 5 // 预编译指令
int main(int argc, const char * argv[] ) {

/*
数组（C语言）
1. 集合
2. 有序
3. 类型相同

int a
int a[常量表达式]

错误示范
int a;
char a[10];
*/


// 定义一个可以存放10个元素的整形数组
int array1[10];
float array2[10];

// 不安全，可能会导致内存越界访问
int nlength = 6;
short array3[nlength];  
nlength = 3;
array3;

// 正确写法
long array4[LENGTH];

return 0;
}