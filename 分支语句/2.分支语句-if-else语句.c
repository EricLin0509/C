// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

/* 
判断
if (条件表达式) 
    语句;

选择
if (条件表达式)
    语句1;
else
    语句2;
 */

int a;
int b;

printf("请输入第一个值\n");
scanf("%d",&a);

printf("请输入第二个值\n");
scanf("%d",&b);

if (a < b)
{
    printf("%d\n",b);
}
else
{
    printf("%d\n",a);
}
    return 0;
}