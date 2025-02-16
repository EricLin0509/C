#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    printf("result = %d\n", *result);
    pthread_exit((void *) result);
}

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    int *result;
    pthread_t thread;
    if (pthread_create(&thread, NULL, &dice, NULL) != 0) 
    {
        perror("pthread_create");
        return 1;
    }

    pthread_exit(NULL);

    if (pthread_join(thread, (void**) &result) != 0)
    {
        perror("pthread_join");
        return 2;
    }
    printf("result = %d\n", *result);
    free(result);
}