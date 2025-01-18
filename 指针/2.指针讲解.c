// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h>  
int main(int argc, const char * argv[] ) {

int a = 20;
int b = 100;
int * p = &a; // 将a的地址给到变量p
p = &b; // 修改变量p存储的内存地址
*p = 200; // 通过地址取值，同时改变了变量b对应的那块内存的值
// 验证
printf("a=%d\n",a);
printf("b=%d\n",b);
printf("p=%d\n",*p); // 说明 *p 指向与b

return 0;
}