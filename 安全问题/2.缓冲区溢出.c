// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {

    /*
    缓冲区溢出是一种常见的攻击手段，它的原理是：

    1. 缓冲区是一段连续的内存空间，它的大小是固定的
    2. 当我们向缓冲区中写入数据时，如果写入的数据的大小超过了缓冲区的大小，那么就会发生缓冲区溢出
    3. 缓冲区溢出会导致缓冲区中的数据被覆盖，从而导致程序的崩溃或者其他的安全问题
    */

    char buffer1[10];
    char buffer2[10] = "Hello";

    printf("%zu\n",buffer1);
    printf("%zu\n",buffer2);

    memcpy(buffer1, "1234567890abcdef", 18);

    printf("%s\n",buffer1);
    printf("%s\n",buffer2); // buffer2 中的数据被覆盖了，导致缓冲区溢出


    char buffer3[10];
    char buffer4[10] = "Hello";

    // gets(buffer3); // gets() 函数是不安全的，它会导致缓冲区溢出
    // 假如我们输入的字符串的长度超过了缓冲区的大小，那么就会发生缓冲区溢出


    // 解决方案

    // 使用 fgets() 函数
    fgets(buffer3, 10, stdin); // fgets() 函数可以限制输入的字符串的长度，从而避免缓冲区溢出
    // 多余的字符依旧会被留在标准输入缓冲区中，等待下一次输入
    
    printf("%s\n",buffer3);
    printf("%s\n",buffer4); // buffer4 中的数据没有被覆盖

    fgets(buffer4, 10, stdin);
    printf("%s\n",buffer4); // 这里数据来自上一次的输入

    return 0;

}