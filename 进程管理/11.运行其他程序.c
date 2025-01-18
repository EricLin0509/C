// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Linux 系统使用这个头文件
// #include <process.h> // // Windows 系统使用这个头文件
#include <sys/wait.h>
#include <errno.h>

int main(int argc, const char * argv[]) {

    // 注意：Windows 下的 execl 函数和 execlp 函数需要在前面添加 '_'

    // execl 函数
    execl("/usr/bin/ping", // 第一个参数是要执行的程序的路径
            "ping", // 第二个参数是要执行的程序的名称
            "www.bing.com", // 后面的参数是要传递给程序的参数
            NULL); // 最后一个参数必须是 NULL
    printf("execl 函数执行完毕\n"); // 这个语句不会执行，因为 execl 函数会替换当前进程的代码
    // 除非第一个参数传递的路径不正确，否则不会执行到这里


    // execlp 函数
    execlp("ping", // 第一个参数是要执行的程序的名称
            "ping", // 第二个参数是要执行的程序的名称
            "www.bing.com", // 后面的参数是要传递给程序的参数
            NULL); // 最后一个参数必须是 NULL
    // execlp 中的 p 表示在环境变量 PATH 中查找要执行的程序的路径


    // execvp 函数
    char *arr[] = {"ping", "www.bing.com", NULL}; // 定义一个字符串数组，用于存储要传递给程序的参数
    execvp("ping", arr); // 第一个参数是要执行的程序的名称，第二个参数是一个字符串数组，用于存储要传递给程序的参数

    int err = errno;

    /*
    相比从终端运行程序，使用 exec 型函数的区别是：
    
    终端运行的是shell脚本，而 exec 型函数运行的是程序本身
    shell 是向终端传参，而 exec 型函数是直接向程序传参

    例如：'ping -c 1 www.bing.com | grep "rtt"' 可以在终端运行，而 exec 型函数无法运行
    因为终端知道 '|' 是管道符，而 exec 型函数不知道 '|' 是管道符
    */

    return 0;
}