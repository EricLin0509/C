#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semFuel;

int fuel = 0; // 全局变量

void *routine1(void *arg)
{
    while (1)
    {
        sem_wait(&semFuel); // 等待信号量
        fuel += 10;
        printf("fuel = %d\n", fuel);
    }
}

void *routine2(void *arg)
{
    while (1)
    {
        sem_post(&semFuel); // 发送信号量
        usleep(5000);
    }
}

int main(int argc, const char * argv[]) {
    pthread_t thread[THREAD_NUM];
    sem_init(&semFuel, 0, 1);
    for (int i = 0; i < THREAD_NUM; i++) {
        if (i % 2 == 0)
        {
            if(pthread_create(thread+i, NULL, &routine1, NULL) != 0)
            {
                perror("pthread_create failed");
                return 1;
            }
        }
        else
        {
            if(pthread_create(thread+i, NULL, &routine2, NULL)!= 0)
            {
                perror("pthread_create failed");
                return 1;
            }
        }
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join failed");
            return 2;
        }
    }
    sem_destroy(&semFuel);
}