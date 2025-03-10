#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mail = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex); // 加锁
        mail++;
        printf("mail: %d\n", mail);
        pthread_mutex_unlock(&mutex); // 解锁
    }   
}

int main(int argc, const char *argv[]) {
    pthread_t thread[5];
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁

    for(int i = 0; i < 5; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
        printf("线程%d启动\n", i);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            return 2;
        }
        printf("线程%d结束\n", i);
    }

    pthread_mutex_destroy(&mutex); // 销毁互斥锁
    printf("mail: %d\n", mail);
}