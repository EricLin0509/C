#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mail = 0;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        mail++;
    }
}

int main(int argc, const char *argv[]) {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &routine, NULL) != 0) {
        return 1;   
    }
    if (pthread_create(&thread2, NULL, &routine, NULL) != 0)
    {
        return 1;
    }
    if (pthread_join(thread1, NULL) != 0)
    {
        return 2;
    }
    if (pthread_join(thread2, NULL) != 0)
    {
        return 2;
    }
    printf("mail: %d\n", mail);
}