# binary信号量

## 什么是binary信号量

binary信号量是一种特殊的信号量，它只能取0和1两个值。当信号量的值为0时，表示资源不可用；当信号量的值为1时，表示资源可用

## 代码示例

### 创建线程

```c
#define THREAD_NUM 1

int *fuel;

int main(int argc, const char *argv[]) {
    fuel = malloc(sizeof(int));
    *fuel = 50;
    pthread_t thread[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join failed");
            return 2;
        }
    }

    return 0;
}
```

### 设置信号量

```c
sem_t semFuel;
```

### 初始化信号量

binary信号量只能取0和1两个值，因此初始化时，信号量的值只能为0或1

```c
#define THREAD_NUM 1

sem_t semFuel;

int *fuel;

int main(int argc, const char *argv[]) {
    pthread_t thread[THREAD_NUM];
    sem_init(&semFuel, 0, 1);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join failed");
            return 2;
        }
    }
    sem_destroy(&semFuel);

    return 0;
}
```


### 添加信号量

```c
#define THREAD_NUM 1

sem_t semFuel;

int *fuel;

void *routine(void *args)
{
    *fuel += 50;
    printf("fuel = %d\n", *fuel);
    sem_post(&semFuel);
}
```


### 等待信号量

```c
#define THREAD_NUM 1

sem_t semFuel;

int *fuel;

int main(int argc, const char *argv[]) {
    fuel = malloc(sizeof(int));
    *fuel = 50;
    pthread_t thread[THREAD_NUM];
    sem_init(&semFuel, 0, 0);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(thread+i, NULL, &routine, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    sem_wait(&semFuel);
    printf("free\n");
    free(fuel);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join failed");
            return 2;
        }
    }
    sem_destroy(&semFuel);

    return 0;
}
```

[源代码](binary信号量.c)

### 运行

```bash
gcc -o binary binary.c -pthread
./binary
fuel = 100
free
```

可以看到，由于信号量的初始值为0，因此主线程会被阻塞，子线程会先运行，运行完后，信号量的值为1，主线程会被唤醒，继续运行

**同时，binary信号量跟mutex的运作方式类似**