# trylock (mutex_trylock) 与lock (mutex_lock) 的区别

## mutex_lock

### 示例

```c
pthread_mutex_t mutex;

void *routine(void *args)
{
    pthread_mutex_lock(&mutex); 
    int info = *(int *)args;
    printf("Thread %d Got lock\n",info);
    sleep(1);
    free(args);
    pthread_mutex_unlock(&mutex); 
}

int main(int argc, const char *argv[]) {
    pthread_t threads[4];
    pthread_mutex_init(& mutex , NULL);
    for (int i = 0; i < 4 ; i++)
    {
        int *pass = malloc(sizeof(int));
        *pass = i+1;
        if (pthread_create (&threads[i], NULL, &routine ,pass) != 0)
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
```

[源代码](mutex_lock.c)

### 运行

```bash
$ gcc -o lock lock.c -pthread
$ ./lock
Thread 3 Got lock
Thread 2 Got lock
Thread 1 Got lock
Thread 4 Got lock
```

### 分析

- 当其中一个线程获取到锁后，其他线程都在等待获取锁
- 那个线程释放锁后，其他线程中只有一个线程能获取到锁，剩下的线程都在等待获取锁

## mutex_trylock

### 函数原型
```c
int pthread_mutex_trylock (pthread_mutex_t *__mutex)
```

### 示例

#### 使用trylock

```c
pthread_mutex_t mutex;

void *routine(void *args)
{
    pthread_mutex_trylock(&mutex);
    printf("Got lock\n");
    sleep(1);
    pthread_mutex_unlock(&mutex); 
}
```

由于 `pthread_mutex_trylock` 只会尝试获取锁，所以要保证每个线程获取到锁后，才能执行后续的操作

```c
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
```

[源代码](mutex_trylock.c)

#### 运行

```bash
$ gcc -o trylock trylock.c -pthread
$ ./trylock
Got lock
Thread didn't locked
Thread didn't locked
Thread didn't locked
```

### 分析
- 当其中一个线程获取到锁后，其他线程不会等待获取锁，而是直接返回


## 总结

| 函数 | mutex_lock | mutex_trylock |
| :---: | :---: | :---: |
| 行为 | 会等待获取锁 | 不会等待获取锁 |
| 用途 | 一般用于线程同步 | 一般用于非阻塞的线程同步 |