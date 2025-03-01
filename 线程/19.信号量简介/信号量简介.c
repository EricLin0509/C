#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void *routine(void *arg)
{
    sem_wait(&semaphore);
    sleep(1);
    printf("Hello from thread %d\n", *(int *)arg);
    free(arg);
    sem_post(&semaphore);
}

int main(int argc, const char *argv[]) {
    pthread_t thread[4];

    sem_init(&semaphore, 0, 2);

    for (int i = 0; i < 4; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        if (pthread_create(&thread[i], NULL, &routine, (void *)a) != 0)
        {
            perror("pthread_create\n");
        }
        
    }
    
    for (int i = 0; i < 4; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join\n");
        }
    }
    sem_destroy(&semaphore);
}