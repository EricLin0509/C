#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *routine(void *arg)
{
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("hello world\n");
    pthread_mutex_unlock(&mutex);
}

int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(&thread[i], NULL, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        int *result;
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }
    // pthread_mutex_destroy(&mutex); // 可以不主动销毁mutex，但最好还是主动销毁

    return 0;
}