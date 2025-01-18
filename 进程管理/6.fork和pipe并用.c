// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 独有的头文件
#include <sys/wait.h>

int main(int argc, const char * argv[]) {

    int arr[] = {1,2,3,4,5};

    int arrSize = sizeof(arr) / sizeof(int);

    int start, end;

    int fd[2];
    if (pipe(fd) == -1)
    {
        return 1;
    }
    
    int id = fork();

    if (id == -1)
    {
        return 2;
    }
    
    if (id == 0)
    {
        start = 0; // 从第一个元素开始
        end = start + arrSize / 2; // 到第三个元素结束
    }
    else
    {
        start = arrSize / 2; // 从第三个元素开始
        end = arrSize; // 到最后一个结束
    }

    int sum = 0;

    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }
    
    printf("Calculated partial sum: %d\n",sum);

    if (id == 0)
    {
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(int)) /*将子进程里的 sum 值写到管道中*/ == -1) // 检查是否写入成功
        {
            return 4;
        }
        close(fd[1]);
    }
    else
    {
        int Childsum; // 用于记录子进程 sum 的值
        close(fd[1]);
        if (read(fd[0], &Childsum, sizeof(Childsum)) /* 读取管道里的值*/ == -1) // 检查是否读取成功
        {
            return 4;
        }

        int total = sum + Childsum;
        printf("Total sum is %d\n",total);
        wait(NULL);
    }

    return 0;
}