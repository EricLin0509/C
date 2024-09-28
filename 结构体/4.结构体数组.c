// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

typedef struct students
{
    int num;
    char name[20];
    char sex;
    int score;
}STUDENT;

int main (int argc, const char * argv[]) {

struct students edu1[3]; // 定义结构体数组

// 数组元素的使用
STUDENT edu[3] = {
    {1001,"James",'M',90},
    {1002,"Bob",'M',78},
    {1003,"Mary",'F',86}
}; // 定义结构体数组并初始化
float sum = 0;

for (int i = 0; i < 3; i++)
{
    sum += edu[i].score;
}
printf("平均分为：%.2lf\n",(float)(sum/3));

return 0;

}