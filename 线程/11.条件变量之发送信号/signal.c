#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
int fuel = 0;

pthread_cond_t condFuel;

void *fuel_filling(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 60;
        printf("加油中... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel); // 发送条件变量
        sleep(1);
    }
}

void *car(void *arg)
{
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40)
    {
        printf("没油了，等待中...\n");
        pthread_cond_wait(&condFuel, &mutexFuel); // 等待条件变量
        // 等价于：
        // pthread_mutex_unlock(&mutexFuel);
        // 等待条件变量
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("请立即加油! 现在剩余：%d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main(int argc, const char * argv[]) {
    pthread_t thread[5];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL); // 初始化条件变量
    for (int i = 0; i < 5; i++)
    {
        if (i == 4)
        {
            if (pthread_create(&thread[i], NULL, &fuel_filling, NULL) != 0)
            {
                perror("pthread_create");
                return 1;
            }
            
        }
        else
        {
            if (pthread_create(&thread[i], NULL, &car, NULL) != 0)
            {
                perror("pthread_create");
                return 1;
            }
            
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel); // 销毁条件变量
    return 0;
}