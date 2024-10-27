// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 独有的头文件
#include <sys/wait.h>

int main(int argc, const char * argv[]) {

    int fd[3][2]; // 创建三个管道
    
    for (int i = 0; i < 3; i++)
    {
        if (pipe(fd[i]) == -1) // 检查是否创建成功
        {
            return 1;
        }
    }

    int id1 = fork();
    if (id1 == -1)
    {
        return 2;
    }

    if (id1 == 0)
    {
        // 子进程1
        close(fd[0][1]); // 关闭读端
        close(fd[1][0]); // 关闭其他管道
        close(fd[2][1]);
        close(fd[2][0]);    
        int x = 0;
        if (read(fd[0][0],&x,sizeof(x)) /*从第一个管道读取*/ == -1)
        {
            return 3;
        }
        x += 5;
        if (write(fd[1][1],&x,sizeof(x)) /*从第二个管道写入*/ == -1) 
        {
            return 4;
        }
        close(fd[0][0]);
        close(fd[1][1]);

        return 0; // 子进程1结束
    }
    
    int id2 = fork();

    if (id2 == -1)
    {
        return 2;
    }

    if (id2 == 0)
    {
        // 子进程2
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        int x = 0;
        if (read(fd[1][0],&x,sizeof(x)) /*从第二个管道读取*/ == -1)
        {
            return 5;
        }

        x += 5;

        if (write(fd[2][1],&x,sizeof(x)) /*从第三个管道写入*/ == -1)
        {
            return 6;
        }
        close(fd[1][0]);
        close(fd[2][1]);

        return 0; // 子进程2结束
    }

    // 父进程
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    int x = 0;
    if (write(fd[0][1],&x,sizeof(x)) /*从第一个管道写入*/ == -1)
    {
        return 8;
    }

    if (read(fd[2][0],&x,sizeof(x)) /*从第三个管道读取*/ == -1)
    {
        return 9;
    }

    printf("result is: %d\n",x);

    close(fd[0][1]);
    close(fd[2][0]);

    waitpid(id1,NULL,0);
    waitpid(id2,NULL,0);

    return 0;
}