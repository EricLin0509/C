// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>

/*
在 C 语言中，会调用两种内存分配方式来分配内存：
一种是栈区的内存分配，由编译器自动分配和释放，通常用于存储局部变量和函数参数
而栈区的内存一旦初始化后，其大小是固定的，无法动态调整
程序运行完成后，栈区的内存会被自动释放

另一种是堆区的内存分配，由程序员手动分配和释放，通常用于存储动态分配的内存
而堆区的内存大小可以根据需要动态调整，因此更加灵活
程序运行完成后，需要手动释放堆区的内存，否则会导致内存泄漏
*/

void myfunc(int c, int d) // 在栈区分配内存
{
    printf("%d %d\n", c, d);
}

void memory_leak(int size)
{
    malloc(size); // 会导致内存泄漏
}

int main(int argc, const char * argv[]) { 

int a = 4; // 在栈区分配内存
int b = 6;
myfunc(a, b); // 传递参数时，会将参数的值复制到栈区的内存中

// malloc() 函数
int *p = malloc(sizeof(int) * 10); // malloc() 函数在堆区分配内存，然后返回一个指向该内存的指针

for (int i = 0; i < 10; i++)
{
    p[i] = 10 - i;
}

for (int i = 0; i < 10; i++)
{
    printf("p[%d]=%d\n", i, p[i]);
}

free(p); // 释放堆区的内存，否则会导致内存泄漏

// while(1) memory_leak(128000); // 会导致内存泄漏

// calloc() 函数
int *p2 = calloc(10, sizeof(int)); // calloc() 函数在堆区分配内存，然后返回一个指向该内存的指针

for (int i = 0; i < 10; i++)
{
    p2[i] = 10 - i;
}

for (int i = 0; i < 10; i++)
{
    printf("p2[%d]=%d\n", i, p2[i]);
}

int *save = p2;
free(p2);

for (int i = 0; i < 10; i++)
{
    printf("save[%d]=%d\n", i, save[i]); // free() 之后，被释放内存里面的内容不会被清空，只是被标记为可用，可能会保留原来的值， 
}
// 如果使用此方法存储密码等敏感信息，需要将其清空，避免被恶意读取

/*
calloc() 和 malloc() 的区别
malloc() 只分配内存，不初始化内存，而 calloc() 会将分配的内存初始化为 0
*/


// realloc() 函数

printf("输入大小：");
int size;
scanf("%d", &size);

int *p3 = calloc(size, sizeof(int)); // 可以设置初始大小

for (int i = 0; i < size; i++)
{
    p3[i] = i;
}

int *p4 = realloc(p3, (size + 5) * sizeof(int)); // realloc() 函数可以重新分配内存，然后返回一个指向该内存的指针
// 注意：realloc() 函数会将原来的内存复制到新的内存中，然后释放原来的内存
for (int i = size; i < (size + 5); i++)
{
    p4[i] = 99;
}

for (int i = 0; i < (size + 5); i++)
{
    printf("p4[%d]=%d\n", i, p4[i]);
}

free(p4);


int *password = calloc(10, sizeof(int));

for (int i = 0; i < 10; i++)
{
    password[i] = scanf("%d", &password[i]);
}

for (int i = 0; i < 10; i++)
{
    password[i] = 0; // 将密码清空
}

free(password);

return 0;
}
