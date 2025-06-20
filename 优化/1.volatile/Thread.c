#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

volatile bool flag = false;

void *func(void *args)
{
    sleep(1);
    flag = true;
    return NULL;
}

int main(int argc, const char *argv[]) {
    pthread_t thread;
    pthread_create(&thread, NULL, func, NULL);

    printf("Waiting for flag to be set...\n");

    while(!flag) {} // 等待flag被设置
    printf("Flag is set!\n");

    pthread_join(thread, NULL);
    return 0;
}