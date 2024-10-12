// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {

// int array[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

int **array = malloc(sizeof(int *) * 3); // 使用 malloc 分配一个指针数组，每个指针指向一个一维数组

for (int i = 0; i < 3; i++)
{
    array[i] = malloc(sizeof(int) * 3); // 为每个指针分配一个一维数组
}


array[1][2] = 5;

printf("array[1][2] = %d\n", array[1][2]); // 5

/*
array 存储的是指针数组，每个指针指向一个一维数组的首地址
每一个一维数组里面有三个元素的地址

相比存放在栈区的二维数组，通过动态内存分配得到的二维数组，会占用更多的内存
因为存放在栈区的二维数组只需存放9个元素
而通过动态内存分配得到的二维数组会有9个元素加4个指针的地址
*/

// 清理二维数组的内存
for (int i = 0; i < 3; i++)
{
    free(array[i]); // 先释放每个一维数组的内存
}

free(array); // 再释放指针数组的内存

return 0;

}