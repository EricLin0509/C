// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

typedef struct students
{
    int num;
    char name[20];
    float score;
}STUDENT;

int main(int argc, const char * argv[]) {

STUDENT edu[3];
printf("&edu=%zu\n",&edu);
printf("&edu+1=%zu\n",&edu+1); // 跳过整个结构体数组的大小
printf("&edu[0]=%zu\n",&edu[0]);
printf("&edu[0]+1=%zu\n",&edu[0]+1); // 跳过一个结构体数组的大小
printf("&(edu[0].num)=%zu\n",&(edu[0].num));
printf("&(edu[0].num)+1=%zu\n",&(edu[0].num)+1); // 跳过一个结构体成员的大小
printf("edu=%zu\n",edu); // &edu[0] 与 edu 是一样的
printf("edu+1=%zu\n",edu+1);
/*
&edu, &edu[0], &(edu[0].num), edu 都指向同一个内存地址，但是类型不同
*/

return 0;

}