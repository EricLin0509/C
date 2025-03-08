# 从信号量获取值

## 代码示例

### 初始化

```c
#define  THREAD_NUM 4

sem_t semaphore;

void *routine(void *arg)
{
    int index = *(int *)arg;
    sem_wait(&semaphore);
    sem_post(&semaphore);
    free(arg);
}

int main(int argc, const char *argv[]) {
    pthread_t thread[THREAD_NUM];

    sem_init(&semaphore, 0, THREAD_NUM);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        if (pthread_create(&thread[i], NULL, &routine, (void *)a) != 0)
        {
            perror("pthread_create\n");
        }
        
    }
    
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("pthread_join\n");
        }
    }
    sem_destroy(&semaphore);
}
```

### 获取信号量的值

使用`sem_getvalue`将信号量的值赋值给`semValue`

```c
sem_t semaphore;

void *routine(void *arg)
{
    int index = *(int *)arg;
    int semValue;
    sem_wait(&semaphore);
    sem_getvalue(&semaphore, &semValue); // 赋值给semValue
    printf("(%d) semaphore value: %d\n", index, semValue);
    sem_post(&semaphore);
    free(arg);
}
```

#### 运行结果

```bash
gcc -o semaphore semaphore.c -pthread
./semaphore
(0) semaphore value: 3
(3) semaphore value: 2
(2) semaphore value: 1
(1) semaphore value: 2
```

可以看到，获取到的信号量的值是不确定的

#### 调试

```c
sem_t semaphore;

void *routine(void *arg)
{
    int index = *(int *)arg;
    int semValue;
    sem_wait(&semaphore);
    sem_getvalue(&semaphore, &semValue); // 赋值给semValue
    printf("(%d) semaphore value after wait: %d\n", index, semValue);
    sem_post(&semaphore);
    sem_getvalue(&semaphore, &semValue);
    printf("(%d) semaphore value after post: %d\n", index, semValue);
    free(arg);
}
```

#### 再次运行

```bash
./semaphore
(0) semaphore value after wait: 3
(0) semaphore value after post: 3
(3) semaphore value after wait: 2
(3) semaphore value after post: 2
(2) semaphore value after wait: 1
(2) semaphore value after post: 1
(1) semaphore value after wait: 2
(1) semaphore value after post: 2
```

可以看到，获取到的值在`wait`和`post`之间是一样的，说明出现了竞态条件


#### 解决

使用sleep解决

```c
sem_t semaphore;

void *routine(void *arg)
{
    int index = *(int *)arg;
    int semValue;
    sem_wait(&semaphore);
    sleep(index + 1);
    sem_getvalue(&semaphore, &semValue); // 赋值给semValue
    printf("(%d) semaphore value after wait: %d\n", index, semValue);
    sem_post(&semaphore);
    printf("(%d) semaphore value after post: %d\n", index, semValue);
    free(arg);
}
```

#### 再次运行

```bash
./semaphore
(0) semaphore value after wait: 0
(0) semaphore value after post: 1
(1) semaphore value after wait: 1
(1) semaphore value after post: 2
(2) semaphore value after wait: 2
(2) semaphore value after post: 3
(3) semaphore value after wait: 3
(3) semaphore value after post: 4
```

可以看到，获取到的值是正确的