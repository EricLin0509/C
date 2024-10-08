// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

/*
位段是一种数据结构，允许在一个结构体中以位为单位来指定其成员所占内存长度，这种以位为单位的成员称为“位段”或称“位域”(bit field)。利用位段能够用较少的位数存储数据。
*/

struct students
{
    unsigned int a:2;
    unsigned int b:6;
    unsigned int c:4;
    unsigned int d:4;
    unsigned int i;
};

struct students2
{
    char a:7;
    // char a:9; // 错误，字符型位段不能大于 8 位
    char b:7;
    char c:2;
    unsigned : 2; // 2 位的无名位段，跳过 2 位
    int d:30;
};

int main(int argc, const char * argv[]){

struct students data;

printf("sizeof(boy) = %d\n", sizeof(data));
printf("&data=%zu\n", &data);
printf("&(data.i)=%zu\n", &(data.i));
// 不能取位段的地址，因为位段可能不是一个完整的字节，也不能取地址

data.a = 2; // 2 的 2 进制表示为 10
printf("data.a=%u\n", data.a);

data.a = 5;
printf("data.a=%u\n", data.a); // 101 超过 2 位，取 01

// 位段成员的类型只能是 int unsigned int signed int 或者 char 类型

struct students2 data2;

printf("sizeof(data2) = %d\n", sizeof(data2));

return 0;
}