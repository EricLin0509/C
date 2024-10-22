// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 独有的头文件

int main(int argc, const char * argv[]) {

    int id = fork(); // fork() 创建一个子进程
    // fork(); // 调用 2 次 fork() 会创建 2^2 = 4 个子进程
    printf("Hello world from id: %d\n\n", id); // 在父进程和子进程中都会执行
    // 0 表示子进程，非 0 表示父进程

    if (id == 0) // 控制子进程和父进程的执行逻辑
    {
        printf("Hello world from child process\n");
        exit(0); // 退出子进程
    }
    else
    {
        printf("Hello world from main process\n\n");
    }


    // 创建3个进程

    int id2 = fork();

    if (id2 != 0)
    {
        fork();
    }
    printf("Hello world!\n");
    return 0;
}