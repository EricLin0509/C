// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

/*
= 赋值运算符(变量=表达式)
+ 加
- 减
* 乘
/  对于整型为除法取整运算(5/2=2)
    对于浮点数为通常意义上的除法运算(5.0/2.0=2.5)
% 求余(5%2=1) 
*/

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
    
    int x = 1;
    printf("x=%d\n",x-1);

    int n =5;
    int k = 2;
    int m = n%k;
    printf("m=%d\n",m);

    int a = 7;
    int b = 3;
    int q = 4;
    int p = (a-b)/q;
    printf("p=%d\n",p);

    int c = 1;
    int d = 1;
    printf("x=%d\n",(a+b)/(c*d));

    int g = (a*b)%c;
    printf("g=%d\n",g);
}