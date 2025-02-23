#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUM 2

void *routine(void *arg)
{
    sleep(1);
    printf("Finished\n");
}

int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];

    pthread_attr_t DetachAttr;

    pthread_attr_init(&DetachAttr);
    pthread_attr_setdetachstate(&DetachAttr, PTHREAD_CREATE_DETACHED);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(&thread[i], &DetachAttr, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    pthread_attr_destroy(&DetachAttr);

    pthread_exit(NULL); // 等待其他线程结束，防止主线程提前结束

    return 0;
}