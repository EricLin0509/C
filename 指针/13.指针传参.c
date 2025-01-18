// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>

// 一级指针传参
void print(int *ptr, int sz)
{
    printf("ptr: %zu\n\n",ptr);
    for (int i = 0; i < sz; i++)
    {
        printf("%d ",*(ptr+i));
    }   
}


// 二级指针传参
void pass(int **p2)
{
    **p2 = 20;
    printf("*p2: %zu\n",*p2);
}

int main(int argc, const char * argv[]) {

int arr[10] = {1,2,3,4,5,6,7,8,9,10};
int *p = arr;

int sz = sizeof(arr) / sizeof(int);
//p是一级指针
printf("p: %zu\n",p);
print(p,sz);
printf("\n\n");


int a = 10;
int *pa = &a; // pa是一级指针
int **ppa = &pa;  // ppa是二级指针
pass(ppa);
printf("pa: %zu\n",pa);
printf("*ppa: %zu\n",*ppa); // pa、p2、ppa 存储的地址相同
printf("**ppa: %d\n",**ppa);
printf("*pa: %d\n",*pa);
printf("a: %d\n",a);

return 0;

}