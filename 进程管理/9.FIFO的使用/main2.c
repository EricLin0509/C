// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 独有的头文件
#include <sys/wait.h>

#include <sys/stat.h> // 文件操作相关的头文件
#include <fcntl.h> // 文件控制相关的头文件
#include <sys/types.h>
#include <errno.h>

int main(int argc, const char * argv[]) {

    if (mkfifo("myfifo", 0777) == -1)
    {
        if (errno !=EEXIST)
        {
            printf("Couldn't create fifo fifle\n");
            return 1;
        }
    }

    int arr[5];
    int fd = open("myfifo", O_RDONLY);
    if (fd == -1)
    {
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        if (read(fd, &arr[i], sizeof(int)) == -1) // 从管道文件中读取数据
        {
            return 2;
        }
        printf("Reading %d\n", arr[i]);
    }
    close(fd);
    puts("\n");

    // 重新打开管道文件，写入数据
    fd = open("myfifo", O_WRONLY);
    if (fd == -1)
    {
        return 1;
    }

    if (write(fd, arr, sizeof(int) * 5) == -1)  // 一次写入全部数据
    {
        return 2;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("Writing %d\n", arr[i]);
    }
    close(fd);

    return 0;
}