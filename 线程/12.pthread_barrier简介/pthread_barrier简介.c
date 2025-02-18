#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_barrier_t barrier;

void *routine(void *args)
{
    printf("Waiting at the barrier....\n");
    sleep(1);
    pthread_barrier_wait(&barrier);
    printf("Passed barrier\n");
    sleep(1);
}

int main(int argc, const char *argv[]) {
    pthread_t thread[9];
    pthread_barrier_init(&barrier, NULL, 3);

    for(int i = 0; i < 9; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    for(int i = 0; i < 9; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join failed");
            return 2;
        }
    }
    pthread_barrier_destroy(&barrier);
}