// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

/*
                    逻辑值                                                      数学值
5 > 3 真用数字1表示 假用0表示（非0为真）
5 + 3                                                                                   8
7的逻辑值为1

优先级（从高到低）
()  括号 优先级最高
!   逻辑非
算数运算符
关系
逻辑
赋值

浮点型只能比较大小（小数位要一致才能比）

&& 逻辑与
||    逻辑或
！  逻辑非
&    and

真&&真 为 真
真&&假 为 假
假&&假 为 假
假&&真 为 假
有假为假    第一个表达式为假 则不需要再运算第二个表达式

真 || 真 为 真
真 || 真 为 真
假 || 真 为 真
假 || 假 为 假
有真为真    第一个表达式为真 则不需要再运算第二个表达式
*/

#include  <stdio.h> 
int main(int argc, const char * argv[] ) {

int a = 3;
int b = 4;
int c = 5;
int x;
int y;
printf("C1=%d\n",a+b>c&&b==c); // 0
printf("C2=%d\n",a||b+c&&b-c); // 1
printf("C3=%d\n",!(a>b)&&(!c||1)); // 1
printf("C4=%d\n",!(x=a)&&(y=b)&&0); // 0
printf("C5=%d\n",!(a+b)+c-1&&b+c/2); // 1

return 0;
}