// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include  <stdio.h> 
#include <stdint.h>

int main(int argc, const char * argv[] ) {
 
    // size_t 是无符号整型 (unsigned int)

    int _int = 2147483647; // 2147483647 是 int 的最大值
    printf("_int: %d\n",_int+1); // 2147483648 会导致溢出，变成负数

    size_t _size_t = 2147483647;
    printf("_size_t: %zu\n",_size_t+1); // 2147483648 不会导致溢出，还是 2147483648
    // %zu 是无符号整型的占位符，z是 size_t 的缩写，u是 unsigned 的缩写

    /*
    unsigned int 和 int 的区别
    unsigned int 是无符号整型，它的取值范围是 0 到 2^32-1
    int 是有符号整型，它的取值范围是 -2^31 到 2^31-1
    */

   printf("SIZE_MAX: %zu\n",SIZE_MAX); // SIZE_MAX 是 size_t 的最大值，它的值在64位系统上是 2^64-1，在32位系统上是 2^32-1

    return 0;
}