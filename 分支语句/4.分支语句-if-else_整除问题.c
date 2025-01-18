// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

printf("请输入两个整数：\n");

int a = 0;
int b = 0;

printf("a=");
scanf("%d",&a);
printf("b=");
scanf("%d",&b);

if (b % a == 0)
{
    printf("可以被整除\n");
}
else
{
    printf("不可以被整除\n");
}

return 0;
}