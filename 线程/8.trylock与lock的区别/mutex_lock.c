#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *routine(void *args)
{
    pthread_mutex_lock(&mutex);
    int info = *(int *)args;
    printf("Thread %d Got lock\n", info);
    sleep(1);
    free(args);
    pthread_mutex_unlock(&mutex); 
}

int main(int argc, const char *argv[]) {
    pthread_t threads[4];
    pthread_mutex_init(& mutex , NULL );
    for (int i = 0; i < 4 ; i++)
    {
        int *pass = malloc(sizeof(int));
        *pass = i+1;
        if (pthread_create(&threads[i], NULL, &routine ,pass) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (pthread_join(threads[i], NULL ) != 0)
        {
            perror("pthread_create");
            return 2;
        }
    }

    pthread_mutex_destroy(&mutex);
    return  0 ;
}