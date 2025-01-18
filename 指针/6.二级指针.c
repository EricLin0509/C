// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>

int main(int argc, const char * argv[]) {

int a = 10;
int *pa = &a; // pa 是指针变量，一级指针

// ppa 就是二级指针变量
int* *ppa = &pa; // pa 也是个变量，&pa 取出 pa 在内存中起始地址

return 0;

}
