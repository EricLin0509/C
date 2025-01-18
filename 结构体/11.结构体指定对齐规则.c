// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

// #pragma pack(value) // 设置默认对齐数为 value
// value 只能是 1 2 4 8 等 2 的 n 次方数

/*
结构体成员中，占字节数最大的成员和 value 比较
取最小值为结构体对齐数
*/

#pragma pack(2)

struct students
{
    char a;
    int b;
};

int main(int argc, const char * argv[]){

struct students boy;

printf("sizeof(boy) = %d\n", sizeof(boy)); // 输出6
printf("&(boy.a) = %zu\n", &(boy.a));
printf("&(boy.b) = %zu\n", &(boy.b)); // 相差2

return 0;

}