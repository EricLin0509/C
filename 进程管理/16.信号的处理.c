// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 

void handle_sigtstp(int signal) // 暂停
{
    printf("\nStop not allowed!\n");
    return;
}

void handle_sigcont(int signal) // 继续运行
{
    printf("\nInput a number: ");
    fflush(stdout);
    return;
}

int main(int argc, const char * argv[]) {

    // 注册信号处理函数
    struct sigaction sa; // 定义一个sigaction结构体变量，用于设置信号处理函数
    sa.sa_handler = &handle_sigcont; // 设置信号处理函数为handle_sigstp (暂停)
    sa.sa_flags = SA_RESTART; // 重新启动被暂停的系统调用
    sigaction(SIGCONT, &sa, NULL); // 注册信号处理函数
    // SIGTSTP 是暂停信号的信号编号
    // &sa 是指向sigaction结构体的指针
    // NULL 表示不修改信号处理行为的其他成员

    // 注册信号处理函数
    signal(SIGINT, &handle_sigtstp); // 处理SIGINT信号 (中断)

    int x ;
    printf("Input a number: ");
    scanf("%d",&x);
    printf("x = %d\n",x);

    /*
    结果：

    按下ctrl + c，程序依旧在前台运行，并输出 "Stop not allowed!"
    */

    return 0;
}