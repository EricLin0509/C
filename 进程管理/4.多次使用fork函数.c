// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 独有的头文件
#include <sys/wait.h>
#include <errno.h> // 错误码头文件

int main(int argc, const char * argv[]) {

    int id1 = fork();
    int id2 = fork(); // 记录进程ID

    /*
    进程简化模型：

    进程1 ：id1 = x, id2 = z
    进程2 ：id1 = 0, id2 = y
    进程3 ：id1 = 0, id2 = 0
    进程4 ：id1 = x, id2 = 0


    进程1 > 进程4
    v
    进程2
    v
    进程3
    */
    
    if (id1 == 0)
    {
        if (id2 == 0)
        {
            printf("I am process 3, my id is %d, parent id is %d\n",getpid(),getppid());
        }
        else
        {
            printf("I am process 2, my id is %d, parent id is %d\n",getpid(),getppid());
        }
    }

    if (id1!= 0)
    {
        if (id2 != 0)
        {
            printf("I am process 1, my id is %d, parent id is %d\n",getpid(),getppid());
        }
        else
        {
            printf("I am process 4, my id is %d, parent id is %d\n",getpid(),getppid());
        }
    }
    else
    {
        if (id2== 0)
        {
            printf("I am process 3, my id is %d, parent id is %d\n",getpid(),getppid());
        }
        else
        {
            printf("I am process 2, my id is %d, parent id is %d\n",getpid(),getppid());
        }
    }
    
    // wait(NULL); // 这样会导致僵尸进程的产生
    // 原因是如果进程4先结束，那么进程1就会继续执行到结束，而进程2和进程3可能会变成僵尸进程

    // 解决方法：

    while (wait(NULL) != -1 || errno != ECHILD) // 等待所有子进程结束
    /*
    wait(NULL)!= -1 表示没有子进程结束
    errno 用于指示在程序运行过程中发生的错误
    ECHILD 表示没有子进程
    */
    {
        printf("Waiting...\n");
    }
 
    return 0;
}