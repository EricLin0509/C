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


void Swap(char *buffer1, char *buffer2, int width)
{
    for (int i = 0; i < width; i++)
    {
        char temp = *buffer1;
        *buffer1 = *buffer2;
        *buffer2 = temp;
        buffer1++;
        buffer2++;
    }
    
}

// 实现一个冒泡程序的通用算法
void bubble_sort(void *base, int size, int width, int (*cmp)(const void *e1, const void *e2))
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size- 1 - i; j++)
        {
            // 两个元素比较
            // arr[j] arr[j+1]
            printf("%zu\n",((char *)base+j*width));
            if (cmp((char *)base+j*width, (char *)base+(j+1)*width) < 0) // 条件是第一个元素小于第二个元素
            {
                // 交换
                Swap((char *)base+j*width, (char *)base+(j+1)*width, width);
            }
            
        }
        
    }
    
}

int compare_int(const void *num1, const void *num2)
{
    return *(int *)num1 - *(int *)num2; // 此处将 'void *' 强制转换成 'int *'，然后再解引用
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
printf("\n\n");


// 实现一个冒泡程序的通用算法
int size = sizeof(arr) / sizeof(int);
bubble_sort(arr, size, sizeof(int),compare_int);

for (int i = 0; i < size; i++)
{
    printf("%d ",arr[i]);
}
printf("\n");

return 0;

}