// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>

int Plus(int x, int y)
{
    return x + y;
}

int Minus(int x, int y)
{
    return x - y;
}

int Multiply(int x, int y)
{
    return x * y;
}

int Devide(int x, int y)
{
    return x / y;
}

int (*Choice())(int,int)
{
    int option = 0;
    printf("选择一个选项\n");
    printf("1. 加\n");
    printf("2. 减\n");
    printf("3. 乘\n");
    printf("4. 除\n");
    printf("请输入：");
    scanf("%d",&option);
    switch (option)
    {
    case 1:
        return Plus;
        break;

    case 2:
        return Minus;
        break;

    case 3:
        return Multiply;
        break;

    case 4:
        return Devide;
        break;
    
    default:
        return NULL;
        break;
    }
}

int main(int argc, const char * argv[]) {

int (*pArr[2])(int,int) = {Plus,Minus}; // pArr  就是函数指针数组

int a = 0,b = 0;
printf("请输入两个数：");
scanf("%d",&a);
scanf("%d",&b);
int (*operation)(int,int) = Choice();
printf("结果：%d\n",operation(a,b));

return 0;

}

