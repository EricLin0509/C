// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 独有的头文件
#include <sys/wait.h> // wait 函数的头文件

void counter()
{

    int id = fork();
    int n;
    if (id == 0)
    {
        n = 1;
    }
    else
    {
        n = 6;
    }

    for (int i = n; i < n + 5; i++)
    {
        printf("%d ", i); // 输出的顺序是不确定的
        fflush(stdout); // 刷新缓冲区
    }
    // 问题：子进程和父进程同时输出，输出的顺序是不确定的
    printf("\n");
}


// 解决方案：使用 wait 函数，等待子进程结束后再输出
void counter_fix()
{

    int id = fork();
    int n;
    if (id == 0)
    {
        n = 1;
    }
    else
    {
        n = 6;
    }

    if (id != 0) // 检测是否是父进程，不检测的话，子进程也会执行 wait 函数，导致死锁
    {
       wait(0); // 等待子进程结束
    }
    

    for (int i = n; i < n + 5; i++)
    {
        printf("%d ", i); // 输出的顺序是不确定的
        fflush(stdout); // 刷新缓冲区
    }

    printf("\n");
}

int main(int argc, const char * argv[]) {

    // counter(); // 可以看到输出的顺序是不确定的

    puts("\n");

    counter_fix(); // 可以看到输出的顺序是确定的

    return 0;
}