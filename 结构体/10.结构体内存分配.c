// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

struct students
{
    int num;
    int age;
};

struct students2
{
    char sex;
    int age;
};

int main(int argc, const char * argv[]) {

struct students boy;
printf("sizeof(boy)=%d\n",sizeof(boy)); // 输出8

struct students2 girl;
printf("sizeof(girl)=%d\n",sizeof(girl)); // 输出8
printf("&girl=%zu\n",&girl);
printf("&(girl.sex)=%zu\n",&(girl.sex));
printf("&(girl.age)=%zu\n",&(girl.age));
/*
结构体的大小是结构体成员中最大成员的整数倍，不足的部分用0补齐
在存入 sex 类型后空了3个字节，存入 age 类型时正好存入了 sex 类型的位置，所以结构体大小为8
*/

return 0;

}