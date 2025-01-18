// Copyright (C) 2024 EricLin
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

void test(const char* str) {}

int main(int argc, const char * argv[]) {

int (*pArr[2])(int,int) = {Plus,Minus}; // pArr  就是函数指针数组

int a = 0,b = 0;
printf("请输入两个数：");
scanf("%d",&a);
scanf("%d",&b);
int (*operation)(int,int) = Choice();
printf("结果：%d\n",operation(a,b));


int (*p)(int,int); // 函数指针
int (* p2[4])(int, int); // 函数指针的数组
// &p2: 取出的是函数指针数组的地址
int (* (*p3)[4])(int, int) = &p2; // p3 就是一个指向 [函数指针的数组] 的指针
printf("%zu\n",p3);

// 函数指针pfun
void (*pfun)(const char *) = test;

//函数指针的数组pfunArr
void (*pfunArr[5])(const char *str);
pfunArr[0] = test;

// 指向函数指针数组pfunArr的指针ppfunArr
void (*(*ppfunArr)[5])(const char *) = &pfunArr;

return 0;

}

