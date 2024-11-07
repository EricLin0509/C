// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, const char * argv[]) {

    // SIGSTOP 表示暂停进程的信号
    // SIGCONT 表示继续进程的信号

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
            usleep(50000); // 微秒级别的睡眠
        }
    }
    else
    {
        kill(pid, SIGSTOP); // 暂停子进程，子进程会停止执行

        int t;

        do
        {
            printf("Time in seconds for execution:");
            scanf("%d", &t);

            if(t > 0)
            {
                kill(pid, SIGCONT); // 继续子进程，子进程会继续执行
                sleep(t); // 子进程会继续执行t秒
                kill(pid, SIGSTOP);
            }

        } while (t > 0);

        kill(pid, SIGKILL); // 杀死子进程，无论子进程是否继续执行，都会被杀死
        wait(NULL);

    }

    return 0;
}