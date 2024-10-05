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

struct students3
{
    char a;
    char b;
    char c;
};

struct students4
{
    short int a;
    short int b;
    short int c;
};

struct students5
{
    short int a;
    char b;
};

struct students6
{
    int a;
    double b;
};

struct students7
{
    char *a;
    char b;
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

struct students3 test;
printf("sizeof(test)=%d\n",sizeof(test)); // 输出3

struct students4 test2;
printf("sizeof(test2)=%d\n",sizeof(test2)); // 输出6

struct students5 test3;
printf("sizeof(test3)=%d\n",sizeof(test3)); // 输出4

struct students6 test4;
printf("sizeof(test4)=%d\n",sizeof(test4)); // 输出16

struct students7 test5;
printf("sizeof(test5)=%d\n",sizeof(test5)); // 输出 8/16, 取决于系统

return 0;

}