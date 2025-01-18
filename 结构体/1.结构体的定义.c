// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

// 结构体是一种数据类型，它是由程序员自己设计的一种数据类型，它可以包含若干个成员
// 每个成员可以是基本数据类型，可以是数组，也可以是指针，也可以是其他的结构体

struct students // 定义一个结构体类型
{
    int age;
    char name[20];
    char sex;
    float score;
};


struct students2
{
    int age;
    char name[20];
    char sex;
    float score;
}kevin,james; // 定义结构体的同时定义结构体变量


struct // 无名结构体，以后将无法再定义该结构体类型的变量
{
    int age;
    char name[20];
    char sex;
    float score;
}lucy,bob;


// 使用 typedef 定义结构体类型
typedef struct students3
{
    int age;
    char name[20];
    char sex;
    float score;
}STUDENT; // 定义结构体类型为 STUDENT

int main (int argc, const char * argv[]) {

struct students kevin;

kevin.age = 20; // 访问结构体成员
strcpy(kevin.name,"Kevin");
kevin.sex = 'M';
kevin.score = 90.5;
printf("kevin.age=%d\n",kevin.age);

lucy.age = 19;
printf("lucy.age=%d\n",lucy.age);

STUDENT rose; // 等价与 'struct students3 rose;'
rose.age = 18;
printf("rose.age=%d\n",rose.age);

return 0;

}