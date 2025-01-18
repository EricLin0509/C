// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h>  
int main(int argc, const char * argv[] ) {

// 通过变量名来访问内存空间
int a = 10;
printf("%p\n",&a);

a =20;
int b = 100;
// 指针是一种数据类型
int * p =&a;
/*
int *：一个指针的类型，* 表示取值
p：指针类型的变量，用于指向一个变量的地址
&a：一个变量的地址
无论是什么类型的指针，存的都是地址
内存地址都是无符号整形
*/

p = &b;
printf("%p\n",&b);
printf("%x\n",p); // 两者输出结果一样
/*
%p：输出指针变量地址
%x：输出十六进制数，%x 表示输出小写字母，%X 表示输出大写字母
*/

// 通过指针修改变量的值
*p = 200;
printf("%d\n",b);
printf("%d\n",*p); // 两者输出结果一样

// sizeof() 指针类型在内存中的大小
printf("int * = %d\n",sizeof(int *));
printf("char * = %d\n",sizeof(char *));
printf("short * = %d\n",sizeof(short *));
printf("long * = %d\n",sizeof(long *));
printf("float * = %d\n",sizeof(float *));
printf("double * = %d\n",sizeof(double *));
/*
所有指针类型在32位操作系统中是4个字节大小
所有指针类型在64位操作系统中是8个字节大小
*/
// 按照 unsigned int 为每一个物理内存分配编号


return 0;
}