#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *args)
{
    int index = *(int *)args;
    printf("%d ", primes[index]);
    free(args);
}

int main(int argc, const char *argv[]) {

    pthread_t thread[10];

    for(int i = 0; i < 10; i++)
    {
        int *index = malloc(sizeof(int));
        *index = i;
        if(pthread_create(&thread[i], NULL, &routine, index) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }
    printf("\n");

    return 0;
}