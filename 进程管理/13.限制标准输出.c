// Copyright (C) 2024 EricLin <ericlin050914@gmail.com>
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, const char * argv[]) {

    int pid = fork();

    if (pid == -1)
    {
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        int file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777); // 创建文件并打开文件，权限为 0777，即所有用户都可以读写
        if (file == -1)
        {
            return 2;
        }
        int file2 = dup2(file, STDOUT_FILENO); // 将文件描述符 1 指向文件，即将标准输出指向 pingResult.txt 文件中
        // STDOUT_FILENO 表示标准输出的文件描述符，对应值为 1

        close(file); // 关闭文件描述符 3，因为不用使用文件描述符 3，所以可以关闭它
        /*
        文件描述符：
        0：标准输入
        1：标准输出
        2：标准错误输出
        3：标准输入
        4：标准输出
        5：标准错误输出
        6：标准错误输出
        7：标准错误输出
        8：标准错误输出
        9：标准错误输出
        10：标准错误输出
        */

        int err = execlp("ping", "ping", "-c", "5", "bing.com", NULL); // err 用于存储执行程序的错误信息
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