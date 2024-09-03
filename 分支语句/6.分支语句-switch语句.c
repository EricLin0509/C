// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <string.h>
int main(int argc, const char * argv[] ) {
/*
int A = 6;
switch(表达式) // 必须能以整数、枚举、char表示
{
    case 常量表达式1:
        语句1;
        break;
    case 常量表达式2:
        语句2;
        break;
    ......
    default:
        语句n;
}
后续语句
*/
int a = 0;
int b = 0;
char c;
scanf("%d",&a);
scanf("%d",&b);
scanf("\n%c",&c);

switch (c)
{
case '+':
    printf("%d\n",a+b);    
    break;
case'-':
    printf("%d\n",a-b);
    break;
case '*':
    printf("%d\n",a*b);
    break;
case '/':
    if (b == 0)
    {
        printf("除数不能为0\n");
    }
    else
    {
        printf("%d\n",a/b);
    }
    break;
default:
    printf("输入错误，请重试\n");
    break;
}

return 0;
}
