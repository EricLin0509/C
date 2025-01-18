// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*
竞态条件是指多个线程同时访问同一个共享资源
并且至少有一个线程尝试去修改这个共享资源

竞态条件的发生往往是由于线程的执行顺序是不可预知的
可能会出现死锁
*/

int balance = 0;

int read_balance()
{
    usleep(250000); // 模拟读取数据的耗时操作
    return balance;
}

void write_balance(int new_balance)
{
    usleep(250000); // 模拟写入数据的耗时操作
    balance = new_balance;
}

void deposit(int amount)
{
    int account_balance = read_balance();
    account_balance += amount;
    write_balance(account_balance);
}

void *deposit_muti(void*amount) // 使用多线程去执行
{
    int account_balance = read_balance();
    account_balance += *((int *)amount); // 先将 void 指针强制转换为 int 指针，再解引用
    write_balance(account_balance);

}

int main(int argc, const char *argv[]) {

    int before = read_balance();
    printf("before: %d\n", before);

    deposit(200);
    deposit(300);

    int after = read_balance();
    printf("after: %d\n", after); // 在单线程应用中，没有出现问题


    // 创建两个线程
    pthread_t thread1;
    pthread_t thread2;

    int deposit1 = 200;
    int deposit2 = 300;

    pthread_create(&thread1, NULL, deposit_muti, (void *)&deposit1);
    pthread_create(&thread2, NULL, deposit_muti, (void *)&deposit2); // 使用两个线程去执行 deposit_muti 函数

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); // 等待两个线程执行完毕

    int after_muti = read_balance();
    printf("after_muti: %d\n", after_muti); // 在多线程应用中，出现问题，

    return 0;
}