// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 独有的头文件
#include <sys/wait.h>

int main(int argc, const char * argv[]) {

    /*
    进程ID是一个非负整数，它是一个数字，代表一个进程 
    */

    int id = fork();

    if (id == 0)
    {
        sleep(1); // 子进程睡眠1秒，保证父进程先完成
    }

    /*
    如果父进程先执行完成，那么子进程会重新获取一个新的进程ID
    */

    /*
    假如进程ID在运行时发生改变，容易造成僵尸进程
    因为父进程可能会等待子进程的退出，而子进程的进程ID可能会被重用，导致父进程无法正确等待子进程的退出
    由于僵尸进程无法被回收，会导致内存泄漏，影响系统的性能
    */
    
    printf("Currernt ID: %d\n",getpid()); // getpid() 函数可以获取当前进程的进程ID
    printf("Parent ID: %d\n",getppid()); // getppid() 函数可以获取当前进程的父进程ID

    // 僵尸进程的处理

    // 父进程等待子进程退出

    int res = wait(NULL); // 等待子进程退出，获取子进程的退出状态

    if (res == -1) // 如果等待失败，wait() 会返回 -1
    {
        printf("No child process to wait\n");
        exit(1);
    }
    
    return 0;
}