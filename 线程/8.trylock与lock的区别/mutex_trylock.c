#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void *routine(void *args)
{
    if (pthread_mutex_trylock(&mutex) == 0)
    {
        printf("Got lock\n");
        sleep(1);
        free(args);
        pthread_mutex_unlock(&mutex); 
    }
    else
    {
        printf("Thread didn't locked\n");
    }
}

int main(int argc, const char *argv[]) {
    pthread_t threads[4];
    pthread_mutex_init(& mutex , NULL);
    for (int i = 0; i < 4 ; i++)
    {
        int *pass = malloc(sizeof(int));
        *pass = i+1;
        if (pthread_create (&threads[i], NULL, &routine ,NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (pthread_join(threads[i], NULL ) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }

    pthread_mutex_destroy(&mutex);
    return  0 ;
}