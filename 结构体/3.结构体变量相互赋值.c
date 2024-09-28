// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>

struct students
{
    int num;
    char name[20];
    char sex;
};

struct students2
{
    char name[20];
    int num;
    char sex;
};

int main (int argc, const char * argv[]) {

struct students jame = {1001,"James",'M'};

struct students boy = jame; // 相同类型的结构体变量可以相互赋值
printf("boy.num=%d\n",boy.num);
printf("boy.name=%s\n",boy.name);
printf("boy.sex=%c\n",boy.sex);

struct students2 bob = {"Bob",1002,'M'};
// struct students boy = bob; // ❌ 不同类型的结构体变量不能相互赋值

return 0;

}