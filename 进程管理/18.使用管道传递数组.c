// Copyright (C) 2024 EricLin
// SPDX-License-Identifier: GPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, const char * argv[]) {

    int fd[2][2];
    for (int i = 0; i < 2; i++)
    {
        if (pipe(fd[i]) == -1)
        {
            return 2;
        }
    }
    


    int pid = fork();
    if (pid == -1)
    {
        return 1;
    }

    if (pid == 0)
    {
        // 子进程
        close(fd[0][0]);
        close(fd[1][0]);
        int n;
        int arr[10];
        srand(time(NULL));
        n = rand() % 10 + 1;
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 11;
        }
        if (write(fd[0][1], arr, (sizeof(int) * n)) < 0)
        {
            return 3;
        }
        if (write(fd[1][1], &n, sizeof(int)) < 0)
        {
            return 3;
        }

        close(fd[0][1]);
        close(fd[1][1]);
    }
    else
    {
        // 父进程
        close(fd[0][1]);
        close(fd[1][1]);
        int arr[10];
        int n;
        int sum = 0;
        
        if (read(fd[0][0], arr, (sizeof(int) * 10)) < 0)
        {
            return 4;
        }

        if (read(fd[1][0], &n, sizeof(int)) < 0)
        {
            return 4;
        }

        close(fd[0][0]);
        close(fd[1][0]);

        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
            sum += arr[i];
        }
        printf("\n");
        printf("sum = %d\n", sum);
        wait(NULL);


    }
    

    return 0;
}