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

    // pipe 的局限性
    /*
    1. 只能配合 fork 函数使用
    2. 只能单向通信
    3. 只能在有血缘关系的进程之间使用
    */


   // FIFO 命名管道
   /*
    1. 可以在没有血缘关系的进程之间使用
    2. 可以实现双向通信
    3. 可以在没有读进程或者写进程的情况下打开管道
    4. 可以通过 open 函数打开一个已经存在的管道
    5. 可以使用 unlink 函数删除一个已经存在的管道
   */

    
    // mkfifo("myfifo", 0777); // 创建一个命名管道，myfifo 是管道的名字，0777 是管道的权限，0777 表示所有用户都可以读写
    // 会在当前目录下创建一个 myfifo 文件，这个文件就是一个管道文件

    if (mkfifo("myfifo", 0777) == -1) // 检查是否创建成功
    {
        if (errno !=EEXIST) // 如果创建失败，并且不是因为管道已经存在而报错
        {
            printf("Couldn't create fifo fifle\n");
            return 1;
        }
    }

    printf("Opening...\n");
    int fd = open("myfifo", O_WRONLY); // 打开管道文件，O_WRONLY 表示只写

    /*
    注意：myfifo 需要两个进程同时打开才能通信，否则会卡住
    cat myfifo 可以查看管道文件中的数据
    */

    printf("Opened\n");
    int x = 97; // 要写入的数据，读取出来的数据是char类型
    if (write(fd, &x, sizeof(int)) /*向管道文件中写入数据*/ == -1)
    {
        return 2;
    }
    printf("Writing\n");
    close(fd); // 关闭管道文件
    printf("Closed\n");

    return 0;
}