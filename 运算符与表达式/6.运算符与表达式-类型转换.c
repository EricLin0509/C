// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
/*
转换形式有：隐式类型转换，显式类型转换

隐式类型转换：编译器自动完成
转换规则为：由低级向高级转换

显式类型转换：直接将某数据转换为指定类型
直接在要转换的数据前，用括号加需要强制的类型
*/
float x = 3.14;
int m = 100;
float n = m + x; // 隐式类型转换
printf("n=%.2lf\n",n);

float y = 1.67;
int z = (int)y; // 显式类型转换
printf("z=%d\n",z);

int a = 0;
scanf("%d",&a);

float b = 0.0f;
scanf("%f",&b);

float c = a + b;
printf("a+b=%f",c);
return 0;
}