// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>

int cnum(char *input) {
int small;
return 0;
/*
int：返回值类型名
cnum：函数名
char *input：参数说明和参数列表
int small：定义局部变量
return 0; ：返回值
*/
}

int max(int a,int b) {

if (a > b)
{
    return a;
}
else
{
    return b;
}

}

long mm(int n) {
int t = 1;
for (int i = 1; i <= n; i++)
{
    t*= i;
}
return t;
}

int main(int argc, const char * argv[]) {

int a = 0;
int b = 0;

scanf("%d",&a);
scanf("%d",&b);

int c= max(a,b);
printf("max = %d\n",c);
printf("%ld",mm(a));

}