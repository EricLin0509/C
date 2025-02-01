#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void* threadFunc()
{
    printf("thread pid = %d\n", getpid());
}
int main(int argc, const char * argv[]) {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &threadFunc, NULL) != 0)
    {
        return 1;
    }
    if (pthread_create(&thread2, NULL, &threadFunc, NULL) != 0)
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
    
    return 0;
}