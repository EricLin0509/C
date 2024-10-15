// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

//警告：不要编译运行此程序

#include <stdio.h>
#include <stdlib.h>

int *allocate()
{
    int *p = malloc(sizeof(int) * 100);
    return p;
}

int main(int argc, const char * argv[]) {

int *p;

size_t p_size = sizeof(int) * 1000000000; // 1000000000 个 int 类型的空间

int gen = 0;

while (1)
{
    p = malloc(p_size); //malloc 一直申请空间，直到内存不足，malloc 失败，p 指向 NULL
    /*
    当 malloc 的内存分配太大，系统内存无法满足时，malloc 会返回 NULL，并且原来的内存不会被释放
    同时原来的内存地址也会丢失，无法清除原来的内存
    NULL 不是一个有效的指针，对它进行操作会导致程序崩溃
    内存泄露会导致程序占用的内存越来越大，性能下降，最终导致程序崩溃
    */

    gen++;
    printf("gen = %d\n", gen);

    if (p == NULL)
    {
        printf("malloc failed!\n");
        break;
    }

}

allocate(); // 此函数运行完成后，会导致原来申请的内存地址丢失，无法清除原来的内存，造成内存泄漏

int *block = allocate(); // 通过一个临时指针来接收 malloc 的返回值，防止内存地址丢失，导致内存泄露

free(block);

return 0;

}