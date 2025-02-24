# 静态初始化

## 先看回Mutex的使用方法

```c
pthread_mutex_t mutex;

void *routine(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("hello world\n");
    pthread_mutex_unlock(&mutex);
}

int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(&thread[i], NULL, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        int *result;
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}
```

其中，使用mutex需要`pthread_mutex_init`和`pthread_mutex_destroy`来初始化和销毁，但是可以使用静态初始化的方式来简化代码

## Mutex的静态初始化

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```
使用`PTHREAD_MUTEX_INITIALIZER`宏来初始化mutex，这样就不需要使用`pthread_mutex_init`和`pthread_mutex_destroy`来初始化和销毁了

```c
#define THREAD_NUM 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *routine(void *arg)
{
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("hello world\n");
    pthread_mutex_unlock(&mutex);
}

int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_create(&thread[i], NULL, &routine, NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for(int i = 0; i < THREAD_NUM; i++)
    {
        int *result;
        if(pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }
    // pthread_mutex_destroy(&mutex); // 可以不主动销毁mutex，但最好还是主动销毁

    return 0;
}
```

[源代码](Mutex静态初始化.c)

### 为什么这里可以不主动销毁mutex？

因为`PTHREAD_MUTEX_INITIALIZER`宏定义的mutex是一个静态变量，大部分的系统都会把静态变量放在数据段中，数据段中的变量在程序结束时会自动销毁，所以这里可以不主动销毁mutex

## 条件变量的静态初始化

```c
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
```
使用`PTHREAD_COND_INITIALIZER`宏来初始化cond，这样就不需要使用`pthread_cond_init`和`pthread_cond_destroy`来初始化和销毁了