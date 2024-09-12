// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

/*
头文件是个在程序设计时，特别是在C语言和C++中使用的文件，通常是源代码的形式，由编译器在处理另一个源文件的时候自动包含进来。一般来说，程序员通过编译器指令将头文件包含进其他源文件的开始。
头文件一般包含类、子程序、变量和其他标识符的前置声明。需要在一个以上源文件中被声明的标识符可以被放在一个头文件中，并在需要的地方包含这个头文件。
*/
#include<stdio.h>
#include "header.h" // 引用私有的 header.h

int main(int argc, const char * argv[]) {
int arr[10] = {4,7,9,10,2,8,1,6,5,3};
int * p = arr;
int len = sizeof(arr)/sizeof(arr[0]); 
printf("%d\n",sizeof(arr));

bubble(p, len); // 此宏定义在 header.h 中声明了

for (int i = 0; i < 10; i++)
{
    printf("%d ",arr[i]);
}
putchar('\n');

return 0;

}