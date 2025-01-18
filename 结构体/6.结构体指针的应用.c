// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

typedef struct students
{
    int num;
    char name[20];
    char sex;
}STUDENT;


// 结构体指针作为函数参数
void func (STUDENT *p)
{
    p -> num = 1001;
    strcpy(p -> name, "Bob");
    p -> sex = 'M';
}

int main (int argc, const char * argv[]) {

STUDENT *p, lucy, bob;
p = &lucy;
p -> num = 1001; // p 指向 num 成员

strcpy(p -> name, "Lucy");
strncpy(p -> name, "Lucy", 20); // 安全的写法

// p -> name = "baby"; // 错误的写法，name 是数组名，不能被赋值


// 结构体指针作为函数参数
func(&bob);
printf("bob.num=%d\n",bob.num);
printf("bob.name=%s\n",bob.name);
printf("bob.sex=%c\n",bob.sex);

return 0;

}