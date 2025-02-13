#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t stoveMutexes[4];
int stoveFuel[4] = {100, 100, 100, 100};

void *routine(void *arg)
{
    for (int i = 0; i < 4; i++)
    {
        if (pthread_mutex_trylock(&stoveMutexes[i]) == 0)
        {
            int NeededFuel = rand() % 30;
            if (stoveFuel[i] - NeededFuel < 0)
            {
                printf("没有足够的燃料\n");   
            }
            else
            {
                stoveFuel[i] -= NeededFuel;
                usleep(500000);
                printf("剩余燃料：%d\n", stoveFuel[i]);
            }
            pthread_mutex_unlock(&stoveMutexes[i]);
            break;
        }
        else
        {
            if (i == 3) // 如果最后一个“炉”也被占用了，就从头开始
            {
                usleep(300000);
                i = 0;
            }
        }
    }
}

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    pthread_t threads[10];
    for (int i = 0; i < 4; i++)
    {
        pthread_mutex_init(&stoveMutexes[i], NULL);
    }
    for (int i = 0; i < 10 ; i++)
    {
        if (pthread_create (&threads[i], NULL, &routine ,NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(threads[i], NULL ) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_mutex_destroy(&stoveMutexes[i]);
    }
    return  0 ;
}