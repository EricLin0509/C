// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>
int main(int argc, const char * argv[]) {

int arr[10] = {1,2,3,4,5,6,7,8,9,10};
int * p = arr;
p++;
*p = 100; // {1,100,3,4,5,6,7,8,9,10}
// p = 100; // 野指针
// *p = 100; // 非法操作野指针内存
p = &arr[9];
*p = 100; // {1,100,3,4,5,6,7,8,9,100}
p--;
*p = 20; // {1,100,3,4,5,6,7,8,20,100}
p=&arr[0];
*p += 100; // {101,100,3,4,5,6,7,8,20,100}
printf("%d\n",p);
p += 100;
printf("%d\n",p);

int len = p - arr; // 什么类型的地址相减就等于什么类型的地址大小
printf("len = %d\n",len);

for (int i = 0; i < 10; i++)
{
    printf("%d\n",arr[i]);
}
putchar('\n');

int arr2[10] = {1,2,3,4,5,6,7,8,9,10};

int * p2 = arr2;

// p2 = &arr[9];
// int length = p2 - arr;
// printf("length= %d\n",length);

for (p2 = arr2; p2 <= &arr2[9]; p2++)
{
    printf("%d\n",*p2);
    // printf("%d\n",p2); 打印出地址
}
putchar('\n');

for (p2 = arr2; p2 < &arr2[10]; p2++)
{
    printf("%d\n",p2[0]);
}


return 0;

}