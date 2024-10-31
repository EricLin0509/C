// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {

    // execlp("ping", "ping", "-c", "5", "www.bing.com", NULL); // 执行ping命令
    // printf("Success!\n"); // 如果ping命令执行成功，但是不会输出 'Success!'

    int pid = fork();

    if (pid == -1)
    {
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        execlp("ping", "ping", "-c", "5", "www.bing.com", NULL); // 在子进程中执行ping命令
        printf("Some message\n"); // 如果ping命令执行成功，但是不会输出 'Some message'
    }
    else
    {
        // Parent process
        wait(NULL); // 等待子进程执行完毕
        printf("Success!\n"); // 在父进程中输出 'Success!'

    }
    

    return 0;
}