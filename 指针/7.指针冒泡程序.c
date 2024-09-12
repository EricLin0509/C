// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include<stdio.h>

void bubble(int *p, int len) {
for (int i = 0; i < len; i++)
{
    for (int j = 0; j < len - 1 - i; j++)
    {
        if (*(p+j) < *(p+j+1))
        {
            int temp = *(p+j);
            *(p+j) = *(p+j+1);
            *(p+j+1) = temp;
        }
        
    }
    
}

}

int main(int argc, const char * argv[]) {
int arr[10] = {4,7,9,10,2,8,1,6,5,3};
// 数组名和指针的区别
// 数组名通过 sizeof 可以求出数组大小
// 指针只包含数组的首地址信息
int * p = arr;
int len = sizeof(arr)/sizeof(arr[0]); // 10
printf("%d\n",sizeof(arr));
// printf("%d\n",sizeof(p));

bubble(p, len);

for (int i = 0; i < 10; i++)
{
    printf("%d ",arr[i]);
}
putchar('\n');

return 0;

}