// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, const char * argv[]) {

    int p[2];
    if (pipe(p) == -1)
    {
        return 1;
    }
    int pid = fork();
    if (pid == -1)
    {
        return 2;
    }
    
    if (pid == 0) // 子进程
    {
        int x;
        if ((read(p[0], &x, sizeof(x))) == -1)
        {
            return 3;
        }
        printf("Received %d\n", x);
        x *= 4;
        if ((write(p[1], &x, sizeof(x))) == -1)
        {
            return 4;
        }
        printf("Sent %d\n", x);
    }
    else // 父进程
    {
        srand(time(NULL));
        int y = rand() % 10;
        if ((write(p[1], &y, sizeof(int))) == -1) // 会在子进程中被阻塞
        {
            return 5;
        }
        printf("Sent %d\n", y);
        if ((read(p[0], &y, sizeof(int))) == -1)
        {
            return 6;
        }
    }

    /*
    此程序的问题：
    子进程和父进程同时对管道进行读写，会导致死锁
    */


   // 解决方法：
   // 创建两个管道
   // 一个用于父进程向子进程发送数据
   // 另一个用于子进程向父进程发送数据

   int p1[2]; // C -> P
   int p2[2]; // P -> C

    if (pipe(p1) == -1 || pipe(p2) == -1)
    {
        return 8;
    }

    int pid1 = fork();

    if (pid1 == -1)
    {
        return 7;
    }

    if (pid1 == 0)
    {
        close(p1[0]);
        close(p2[1]);
        int x;
        if ((read(p2[0], &x, sizeof(x))) == -1)
        {
            return 3;
            x *= 4;
        }
        if ((write(p1[1], &x, sizeof(x))) == -1)
        {
            return 4;
        }
        close(p1[1]);
        close(p2[0]);
    }
    else
    {
        close(p1[1]);
        close(p2[0]);
        srand(time(NULL));
        int y = rand() % 10;
        if ((write(p2[1], &y, sizeof(int))) == -1)
        {
            return 5;
        }
        if ((read(p1[0], &y, sizeof(int))) == -1)
        {
            return 6;
        }
        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}