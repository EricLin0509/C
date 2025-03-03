#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define USER 10
#define MAX_USER 15

sem_t semaphore;

void *routine(void *arg)
{
    printf("(%d) 登录中...\n", *(int *)arg);
    sem_wait(&semaphore);
    printf("(%d) 登录成功！\n", *(int *)arg);
    sleep(rand() % 5 + 1);
    printf("(%d) 退出登录！\n", *(int *)arg);
    free(arg);
    sem_post(&semaphore);
}

int main(int argc, const char *argv[]) {
    pthread_t thread[USER];

    sem_init(&semaphore, 0, MAX_USER);

    for (int i = 0; i < USER; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        if (pthread_create(&thread[i], NULL, &routine, (void *)a) != 0)
        {
            perror("pthread_create\n");
        }
        
    }
    
    for (int i = 0; i < USER; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join\n");
        }
    }
    sem_destroy(&semaphore);
}