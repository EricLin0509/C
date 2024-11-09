// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig)
{
    printf("\nPlease input a number\n");
}


int main(int argc, const char * argv[]) {

    int pid = fork();
    if(pid == -1)
    {
        return 1;
    }

    if(pid == 0)
    {
        // Child Process
        sleep(5);
        kill(getppid(), SIGUSR1); // SIGUSR1 是一个用户自定义的信号
    }
    else
    {
        struct sigaction sa;
        sa.sa_flags = SA_RESTART; // 重启被中断的系统调用
        sa.sa_handler = &handle_sigusr1; // 处理 SIGUSR1 信号的函数
        sigaction(SIGUSR1, &sa, NULL);

        // Parent Process
        int x = 0;
        printf("What is the result of 3 x 7 ?\n");
        scanf("%d", &x);
        if(x == 21)
        {
            printf("You are right!\n");
        }
        else
        {
            printf("You are wrong!\n");
        }
    }

    return 0;
}

/*
结果：
当等待 5 秒后，子进程发送 SIGUSR1 信号给父进程，父进程收到信号后，调用 handle_sigusr1 函数
输出 "Please input a number" 提示用户输入一个数字
*/