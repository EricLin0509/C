// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {

int *array = malloc(sizeof(int) * 3);

array[0] = 2;
array[1] = 3;
array[2] = 6;

printf("array before = %zu\n", array);

array = realloc(array, sizeof(int) * 99999999999);
/*
当 realloc 的内存分配太大，系统内存无法满足时，realloc 会返回 NULL，并且原来的内存不会被释放
NULL 不是一个有效的指针，对它进行操作会导致程序崩溃
*/

printf("array after = %zu\n", array);

free(array);

// array[3] = 10; 此时的 array 已经是 NULL 了，无法访问，同时丢失了原来的内存地址，无法清除原来的内存，造成内存泄漏

puts("\n");

// 解决方法：使用一个临时指针来接收 realloc 的返回值

int *array2 = malloc(sizeof(int) * 3);

array2[0] = 2;
array2[1] = 3;
array2[2] = 6;

int *temp;

printf("array2 before = %zu\n", array2);

temp = realloc(array2, sizeof(int) * 99999999999); // 使用一个临时指针来接收 realloc 的返回值，防止 realloc 失败时，array2 指向了一个无效的内存地址

if (temp != NULL)
{
    array2 = temp; // 如果 realloc 成功，将临时指针赋值给 array2
    printf("array2 after = %zu\n", array2);
}
else
{
    printf("array2 after = %zu\n", array2); // 如果 realloc 失败，array2 仍然指向原来的内存地址
    printf("realloc failed!\n");
}

free(array2);

return 0;

}