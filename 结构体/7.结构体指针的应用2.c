// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

typedef struct students
{
    int num;
    char name[20];
    float score;
}STUDENT;


// 结构体指针作为函数参数
void func(STUDENT *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d %s %f\n",p[i].num,p[i].name,p[i].score);
    }
    
}

int main (int argc, const char * argv[]) {

STUDENT edu[3] = {{1001,"zhangsan",90.5},{1002,"lisi",89.5},{1003,"wangwu",95.5}};

func(edu, 3);

return 0;

}