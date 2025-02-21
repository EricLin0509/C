#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

void *routine(void *arg)
{
    pthread_t th = pthread_self();
    printf("thread ID = %lu\n", th);
    printf("thread syscall ID = %d\n", (pid_t)syscall(SYS_gettid));
}
int main(int argc, const char *argv[]) {

    pthread_t thread[2];

    for(int i = 0; i < 2; i++)
    {
        if(pthread_create(&thread[i], NULL, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
        // printf("thread[%d] = %lu\n", i, thread[i]);
    }

    for(int i = 0; i < 2; i++)
    {
        int *result;
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }

    return 0;
}