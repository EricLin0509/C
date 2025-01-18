// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, const char * argv[]) {

    int pid = fork();
    if (pid == -1)
    {
        return 1;
    }

    if(pid == 0)
    {
        while(1)
        {
            printf("A message\n");
            usleep(50000);
        }
    }
    else
    {
        sleep(1);
        kill(0, SIGKILL); // 杀死子进程，无论子进程是否继续执行，都会被杀死
        wait(NULL);
    }
    /*
    信号是一种软件中断，用于通知进程发生了某种事件
    信号可以被进程捕获并处理，也可以被进程忽略
    信号可以被发送给进程，也可以被发送给进程组或所有进程
    */

    return 0;
}