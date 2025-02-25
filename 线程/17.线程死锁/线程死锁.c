#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mail = 0;
pthread_mutex_t mutex;

pthread_mutex_t mutex2;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        if(i % 2 == 0)
        {
            pthread_mutex_lock(&mutex);
            pthread_mutex_lock(&mutex2);
        }
        else
        {
            pthread_mutex_lock(&mutex2);
            pthread_mutex_lock(&mutex);
        }
        mail++;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutex2);
    }   
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&thread1, NULL, &routine, NULL) != 0) {
        return 1;   
    }
    if (pthread_create(&thread2, NULL, &routine, NULL) != 0)
    {
        return 1;
    }
    if (pthread_join(thread1, NULL) != 0)
    {
        return 2;
    }
    if (pthread_join(thread2, NULL) != 0)
    {
        return 2;
    }
    pthread_mutex_destroy(&mutex);
    printf("mail: %d\n", mail);
}