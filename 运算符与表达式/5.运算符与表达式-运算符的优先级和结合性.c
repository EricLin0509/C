// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {
/*
运算符优先级
逗号运算符<赋值运算符<条件运算符<逻辑运算符<位运算符<关系运算符<算数运算符<特殊运算符

大多数运算符为从左向右执行，例如
a++, a-b+c, a%b, a>=b

赋值运算符为从右向左执行，例如
a=3, a-=b

其它右结合性运算符包括：
前增量(++a)，前减量
逻辑非( ! )，正负号，取地址( & )，sizeof
*/

/*
右结合性
a = b + c       赋值表达式
b + c,c + d    逗号表达式
a>b || c          逻辑表达式
a > b + c       关系表达式
*/
int a,b,c,d;
int e = (a=1,b=a++,c=a*b,d=c++ +b);
/*
a=2
b=1
c=3
d=3
e=3
*/
printf("e=%d\n",e);
printf("a=%d\n",a);
printf("b=%d\n",b);
printf("c=%d\n",c);
printf("d=%d\n",d);

return 0;
}