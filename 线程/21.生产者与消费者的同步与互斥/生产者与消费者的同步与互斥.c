#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 8

int buffer[10];
int count = 0;

pthread_mutex_t mutex;

sem_t empty;
sem_t full;

void *producer(void *arg)
{
    while(1)
    {
        // 生产
        int x = rand() % 100;

        // 放入缓冲区
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    while(1)
    {    
        int y = -1; // 测试是否越界

        // 从缓冲区中取出数据
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // 消耗
        printf("Got %d\n", y);
        sleep(1);
    }
}

int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutex, NULL);

    sem_init(&empty, 0, 10); // 缓冲区为空的情况，初始化为10
    sem_init(&full, 0, 0); // 缓冲区为满的情况，初始化为0

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (i > 0)
        {
            if (pthread_create(&thread[i], NULL, &consumer, NULL) != 0)
            {
                perror("pthread_create");
            }
        }
        else
        {
            if (pthread_create(&thread[i], NULL, &producer, NULL)!= 0)
            {
                perror("pthread_create");
            }
        }
        
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(thread[i], NULL)!= 0)
        {
            perror("pthread_join");
        }
    }
    
    sem_destroy(&empty);
    sem_destroy(&full);

    pthread_mutex_destroy(&mutex);
    return 0;
}