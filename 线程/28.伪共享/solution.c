#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

void *increment(void *arg)
{
    uint64_t *counter = (uint64_t *)arg;
    for (int i = 0; i < 1000000000; i++) // 10亿次操作
    {
        (*counter)++;
    }

    return NULL;
}

int main(void) {

    long cache_line_size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE); // 获取缓存行大小
    printf("cache line size = %ld\n", cache_line_size);

    uint64_t alignas(64) counter1 = 0;
    uint64_t alignas(64) counter2 = 0;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, &counter1);
    pthread_create(&t2, NULL, increment, &counter2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("counter1 = %lu\n", counter1);
    printf("counter2 = %lu\n", counter2);

    return 0;
}