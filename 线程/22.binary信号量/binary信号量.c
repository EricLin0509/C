#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 1

sem_t semFuel;

int *fuel;

void *routine(void *args)
{
    *fuel += 50;
    printf("fuel = %d\n", *fuel);
    sem_post(&semFuel);
}

int main(int argc, const char *argv[]) {
    fuel = malloc(sizeof(int));
    *fuel = 50;
    pthread_t thread[THREAD_NUM];
    sem_init(&semFuel, 0, 0);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    sem_wait(&semFuel);
    printf("free\n");
    free(fuel);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join failed");
            return 2;
        }
    }
    sem_destroy(&semFuel);

    return 0;
}