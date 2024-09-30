// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

struct students
{
    int num;
    char name[20];
    char sex;
};


int main (int argc, const char * argv[]) {

struct  students *p; // 定义结构体指针变量

struct students boy = {1001,"James",'M'};
p = &boy;
printf("sizeof(p)=%d\n",sizeof(p)); // 4/8
printf("%zu\n\n",p);
printf("boy.num=%d\n",boy.num);
printf("(*p).num=%d\n",(*p).num);
printf("p->num=%d\n\n",p->num);

boy.num = 101; // 通过结构体变量名访问结构体成员
(*p).num = 101; // 通过结构体指针变量访问结构体成员
p -> num = 101; // 指针指向的结构体成员，(*p).num 与 p -> num 等价
// 前提指针必须指向一个有效且相同的结构体变量
// 点运算符的优先级高于解引用运算符 *，如果用点运算符，括号是必须的

// *p.num = 101; // ❌

printf("boy.num=%d\n",boy.num); // 数据被修改

return 0;

}