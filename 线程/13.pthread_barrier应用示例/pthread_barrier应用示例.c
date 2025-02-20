#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 10

int diceValues[10];
int status[10] = {0};

pthread_barrier_t barrierRollDice; // 用于保证所有线程都摇完色子
pthread_barrier_t barrierCaculate; // 用于保证所有线程都计算完胜负

void *roll_dice(void *args)
{
    int index = *(int *)args;
    diceValues[index]  = rand() % 6 + 1;
    pthread_barrier_wait(&barrierRollDice); // 保证所有线程都摇完色子
    pthread_barrier_wait(&barrierCaculate); // 保证所有线程都计算完胜负
    if (status[index] == 1)
    {
        printf("(%d rolled %d) I won\n", index, diceValues[index]);
    }
    else
    {
        printf("(%d rolled %d) I lost\n", index, diceValues[index]);
    }
    free(args);
}

int main(int argc, const char *argv[]) {
    pthread_t threads[THREAD_NUM];
    pthread_barrier_init(&barrierRollDice, NULL, THREAD_NUM+1);
    pthread_barrier_init(&barrierCaculate, NULL, THREAD_NUM+1);
    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&threads[i], NULL, &roll_dice, a) != 0)
        {
            perror("pthread_create error");
        }
    }

    pthread_barrier_wait(&barrierRollDice); // 保证所有线程都摇完色子

    int max = 0;
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (diceValues[i] > max)
        {
            max = diceValues[i];
        }
    }
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (diceValues[i] == max)
        {
            status[i] = 1;
        }
        else
        {
            status[i] = 0;
        }
    }

    pthread_barrier_wait(&barrierCaculate); // 保证所有线程都计算完胜负

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join error");
        }
    }
    pthread_barrier_destroy(&barrierRollDice);
    pthread_barrier_destroy(&barrierCaculate);
}