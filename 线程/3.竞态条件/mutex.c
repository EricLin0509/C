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
        pthread_mutex_unlock(&mutex); // 解锁
    }   
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁
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
    pthread_mutex_destroy(&mutex); // 销毁互斥锁
    printf("mail: %d\n", mail);
}