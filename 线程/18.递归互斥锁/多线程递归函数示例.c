#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *routine(void *arg)
{
    pthread_mutex_lock(&mutex);
    
    int *nums = (int *)arg;
    printf("gen %d\n", *nums);
    *nums += 1;
    
    if (*nums < 1000)
    {
        routine(nums);
    }

    pthread_mutex_unlock(&mutex);
}

int main(int argc, const char *argv[]) {
    pthread_t thread[4];
    pthread_mutexattr_t recursive_mutex_attr;
    pthread_mutexattr_init(&recursive_mutex_attr);
    pthread_mutexattr_settype(&recursive_mutex_attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&mutex, &recursive_mutex_attr);
    
    int nums = 0;

    for (int i = 0; i < 4; i++)
    {
        if (pthread_create(&thread[i], NULL, &routine, (void *)&nums) != 0)
        {
            perror("pthread_create\n");
        }
        
    }
    
    for (int i = 0; i < 4; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join\n");
        }
        
    }
    

    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&recursive_mutex_attr);
}