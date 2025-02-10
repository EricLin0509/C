#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *args)
{
    int index = *(int *)args;
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += primes[index+i];
    }
    *(int *)args = sum;
    return args;
    
}

int main(int argc, const char *argv[]) {

    pthread_t thread[2];

    for(int i = 0; i < 2; i++)
    {
        int *pass = malloc(sizeof(int));
        *pass = i * 5;
        if(pthread_create(&thread[i], NULL, &routine, pass) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    int global_sum = 0;

    for(int i = 0; i < 2; i++)
    {
        int *result;
        if(pthread_join(thread[i], (void **) &result) != 0)
        {
            perror("pthread_join");
            return 2;
        }
        global_sum += *result;
        free(result);
    }
    printf("sum = %d\n", global_sum);
    printf("\n");

    return 0;
}