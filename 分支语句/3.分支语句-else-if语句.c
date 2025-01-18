// Copyright (C) 2024 EricLin
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

多选一
else if 语句

if (条件表达式1)
    语句1;
else if (条件表达式2)
    语句2;
else if (条件表达式3)
    语句3;
......
else
    语句n; 
 */

int a = 0;
int b = 0;

scanf("%d",a);
scanf("%d",b);
if (a * b > 5000)
{
    printf("大于5000");
}

else if (a * b < 5000)
{
    printf("小于5000");
}
else
{
    printf("等于5000");
}
    return 0;
}