// Copyright (C) 2024 EricLin
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

struct stu
{
    char a;
    short int b;
    int c;
};

struct stu2
{
    char a;
    int b;
    short int c;
};

struct stu3
{
    char a[10];
    int b;
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

/*
字节对齐
1. char 1字节对齐，即存放 char 类型时，地址必须是1的倍数
2. short int 2字节对齐，即存放 short int 类型时，地址必须是2的倍数
3. int 4字节对齐，即存放 int 类型时，地址必须是4的倍数
4. double 8字节对齐，即存放 double 类型时，地址必须是8的倍数
5. 结构体成员的地址必须是成员自身大小的倍数
*/

struct stu temp;
printf("sizeof(temp)=%d\n",sizeof(temp)); // 输出8
printf("&(temp.a)=%zu\n",&(temp.a));
printf("&(temp.b)=%zu\n",&(temp.b));
printf("&(temp.c)=%zu\n\n",&(temp.c));

struct stu2 temp2;
printf("sizeof(temp2)=%d\n",sizeof(temp2)); // 输出12
printf("&(temp2.a)=%zu\n",&(temp2.a));
printf("&(temp2.b)=%zu\n",&(temp2.b));
printf("&(temp2.c)=%zu\n\n",&(temp2.c));

struct stu3 temp3;
printf("sizeof(temp3)=%d\n",sizeof(temp3)); // 输出16
printf("&(temp3.a)=%zu\n",&(temp3.a));
printf("&(temp3.b)=%zu\n\n",&(temp3.b));

/*
字节对齐的目的是为了提高CPU的访问效率
*/

return 0;

}