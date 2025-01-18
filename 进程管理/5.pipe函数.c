// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 独有的头文件

int main(int argc, const char * argv[]) {

    /*
    pipe 函数：

    功能：创建一个管道，返回两个文件描述符，fd[0] 读，fd[1] 写
    参数：int fd[2] 传入一个数组，数组长度为2，用于接收两个文件描述符
    返回值：成功返回0，失败返回-1
    */

    int fd[2];
    // fd[0] 读，fd[1] 写
    if (pipe(fd) == -1) // 检查管道是否创建成功
    {
        printf("Error creating a pipe\n");
        exit(1);
    }
    int id = fork();

    if (id == -1) // 检查fork是否创建成功
    {
        printf("Error creating a fork\n");
    }
    

    if (id == 0)
    {
        close(fd[0]); // fd[0] 在子进程中关闭，因为子进程只需要写，不需要读
        int x;
        printf("Please input a number:");
        scanf("%d",&x);
        if (write(fd[1], &x, sizeof(int)) /* 将x写入管道*/ == -1) // 检查是否写入成功
        {
            printf("ERROR WRITING TO THE PIPE\n");
            exit(2);
        }
        
        close(fd[1]); // 关闭写端
    }
    else
    {
        close(fd[1]); // fd[1] 在父进程中关闭，因为父进程只需要读，不需要写
        int y;
        if (read(fd[0], &y, sizeof(int)) /* 从管道中读取数据*/ == -1) // 检查是否读取成功
        {
            printf("ERROR READING FROM THE PIPE\n");
            exit(3);
        }
        
        printf("The number from child process is %d\n",y);
        close(fd[0]); // 关闭读端
    }

    return 0;
}