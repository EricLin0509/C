# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

void *thread_test() {
    printf("hello from threads\n");
    sleep(2);
    printf("goodbye from threads\n");
}

int main(int argc, const char * argv[]) {
    pthread_t thread1, thread2;
    if(pthread_create(&thread1, NULL, &thread_test, NULL) != 0)
    {
        printf("pthread create failed\n");
        return 1;
    }

    if(pthread_create(&thread2, NULL, &thread_test, NULL) != 0)
    {
        printf("pthread create failed\n");
        return 1;
    }

    if (pthread_join(thread1, NULL) != 0)
    {
        printf("pthread join failed\n");
        return 2;
    }
    
    if (pthread_join(thread2, NULL) != 0)
    {
        printf("pthread join failed\n");
        return 2;
    }
    return 0;
}