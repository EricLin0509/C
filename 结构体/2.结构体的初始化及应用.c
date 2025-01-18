// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

struct date
{
    int year;
    int mouth;
    int day;

};


struct students
{
    int num;
    char name[20];
    char sex;
    char *addr; // 指针成员
    struct date birthday; // 结构体多级引用
};

int main (int argc, const char * argv[]) {

struct students jame = {1001,"James",'M',"Beijing"};
/*
1001 给了 jame.num 赋值
James 给了 jame.name 赋值
M 给了 jame.sex 赋值
Beijing 给了 jame.addr 赋值
*/

// struct students bob = {1002,,'M'}; // ❌ 错误，缺少 name 成员的值

struct students bob;

bob.num = 1002;
printf("bob.num=%d\n",bob.num);
// bob.name = "Bob"; // bob.name 是一个数组名，是数组的首地址，是一个常量，不能直接赋值
strcpy(bob.name,"Bob"); // ✅
strncpy(bob.name,"Bob",sizeof(bob.name)); // ✅ 安全版本，防止缓冲区溢出
bob.sex = 'M';

// strcpy(bob.addr,"Shanghai"); // ❌ 错误，此处 bob.addr 是一个野指针
bob.addr ="Shanghai"; // ✅ bob.addr 指向了一个常量字符串
printf("bob.addr=%s\n",bob.addr);


// 结构体多级引用
bob.birthday.year = 2002;
bob.birthday.mouth = 7;
bob.birthday.day = 14;
printf("%d, %d, %d\n",bob.birthday.year,bob.birthday.mouth,bob.birthday.day);

return 0;

}