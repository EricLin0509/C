#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define  THREAD_NUM 4

sem_t semaphore;

void *routine(void *arg)
{
    int index = *(int *)arg;
    int semValue;
    sem_wait(&semaphore);
    sleep(index + 1);
    sem_getvalue(&semaphore, &semValue); // 赋值给semValue
    printf("(%d) semaphore value after wait: %d\n", index, semValue);
    sem_post(&semaphore);
    sem_getvalue(&semaphore, &semValue);
    printf("(%d) semaphore value after post: %d\n", index, semValue);
    free(arg);
}

int main(int argc, const char *argv[]) {
    pthread_t thread[THREAD_NUM];

    sem_init(&semaphore, 0, THREAD_NUM);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        if (pthread_create(&thread[i], NULL, &routine, (void *)a) != 0)
        {
            perror("pthread_create\n");
        }
        
    }
    
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join\n");
        }
    }
    sem_destroy(&semaphore);
}