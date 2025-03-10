# 并发与并行

## 并行

并行是指启动多个进程同时执行，多个进程有各自的内存空间，互不干扰，是真正意义上的同时执行

### 示例

```c
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
```

可以看到，程序启动了10个线程，同时执行

### 并行的优缺点

- 优点：充分利用CPU资源，提高效率
- 缺点：内存空间占用大，线程切换开销大

## 并发

并发是指启动多个线程同时执行，多个线程共享一个内存空间，相互之间干扰，是伪同时执行

### 示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mail = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex); // 加锁
        mail++;
        printf("mail: %d\n", mail);
        pthread_mutex_unlock(&mutex); // 解锁
    }   
}

int main(int argc, const char *argv[]) {
    pthread_t thread[5];
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁

    for(int i = 0; i < 5; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
        printf("线程%d启动\n", i);
    }

    for(int i = 0; i < 5; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            return 2;
        }
        printf("线程%d结束\n", i);
    }

    pthread_mutex_destroy(&mutex); // 销毁互斥锁
    printf("mail: %d\n", mail);
}
```

可以看到，程序启动了5个线程，同时执行，但是由于线程之间共享一个内存空间，需要加锁，解锁，防止线程之间的干扰

### 并发的优缺点

- 优点：内存空间占用小，线程切换开销小
- 缺点：无法充分利用CPU资源，效率较低

## 总结

|  | 并行 | 并发 |
| :---: | :---: | :---: |
| 定义 | 启动多个进程同时执行 | 启动多个线程同时执行 |
| 内存空间 | 每个进程有各自的内存空间 | 多个线程共享一个内存空间 |
| 线程切换 | 线程切换开销大 | 线程切换开销小 |
| 效率 | 效率较高 | 效率较低 |