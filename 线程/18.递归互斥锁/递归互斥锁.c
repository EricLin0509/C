#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *routine()
{
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    printf("Hello world!\n");
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;

    pthread_mutexattr_t recursive_mutex_attr;
    pthread_mutexattr_init(&recursive_mutex_attr);
    pthread_mutexattr_settype(&recursive_mutex_attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&mutex, &recursive_mutex_attr);
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
    pthread_mutexattr_destroy(&recursive_mutex_attr);
}