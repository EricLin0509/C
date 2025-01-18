// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]) {

    int pid = fork();

    if (pid == -1)
    {
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        int err = execlp("ping", "ping", "-c", "5", "error_webside", NULL); // err 用于存储执行程序的错误信息
        if (err == -1) // -1 表示执行失败
        {
            printf("Could not find program to execute!\n"); // 注意：此消息不会被打印，因为 execlp 执行后，程序会立即退出，不会执行后续代码
            return 2;
        }
        
    }
    else
    {
        int wait_status; // 用于存储子进程的退出状态
        // Parent process
        wait(&wait_status); // 等待子进程退出
        if (WIFEXITED(wait_status)) // WIFEXITED 用于判断子进程是否退出
        {
            int statusCode = WEXITSTATUS(wait_status); // WEXITSTATUS 用于获取子进程的退出状态
            if (statusCode == 0)
            {
                printf("Success!\n"); // 0 表示成功
                return 0;
            }
            else
            {
                printf("Failed with status code %d\n", statusCode); // 非 0 表示失败
                return 1;
            }
            
        }
        
    }

}