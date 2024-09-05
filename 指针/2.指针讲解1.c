// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h>  
int main(int argc, const char * argv[] ) {

int a = 20;
int b = 100;
int * p = &a;
p = &b; // 修改变量p存储的内存地址
*p = 200;
// 验证
printf("b=%d\n",b);
printf("p=%d\n",*p);

return 0;
}