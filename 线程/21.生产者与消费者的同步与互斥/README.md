# 生产者与消费者的同步与互斥

## 理念

有一个共享的缓冲区，生产者往里面放东西，消费者从里面取东西

- 管理共享缓冲区
- 检查缓冲区是否已满
- 检查缓冲区是否为空

## 创建缓冲区

### 条件

```c
int buffer[10];
int count = 0;
```

### 创建线程

```c
int main(int argc, const char *argv[]) {

    srand(time(NULL));
    pthread_t thread[THREAD_NUM];

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (i % 2 == 0)
        {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0)
            {
                perror("pthread_create");
            }
        }
        else
        {
            if (pthread_create(&th[i], NULL, &consumer, NULL)!= 0)
            {
                perror("pthread_create");
            }
        }
        
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL)!= 0)
        {
            perror("pthread_join");
        }
    }
    
    return 0;
}
```

### 生产者

```c
void *producer(void *arg)
{
    while(1)
    {
        // 生产
        int x = rand() % 100;

        // 放入缓冲区
        buffer[count] = x;
        count++;
    }
}
```

### 消费者

```c
void *consumer(void *arg)
{
    while(1)
    {    
        // 从缓冲区中取出数据
        int y = buffer[count - 1];
        count--;

        // 消耗
        printf("Got %d\n", y);
    }
}
```

### 运行

```zsh
gcc -o main main.c -pthread
./main
Got 0
Got 28
Got 54
Got 28
Got 66
Got 5
Got 76
Got 95
Got 84
Got 98
Got 68
Got 35
Got 41
Got 17
Got 52
Got 66
Got 57
Got 99
Got 77
Got 87
Got 31
Got 52
zsh: segmentation fault (core dumped)  ./main
```

可以看到，程序运行时，会出现段错误，这是因为，生产者和消费者越界访问缓冲区

## 防止越界

### 使用mutex

#### 创建mutex

```c
pthread_mutex_t mutex;
```

#### 生产者和消费者

```c
void *producer(void *arg)
{
    while(1)
    {
        // 生产
        int x = rand() % 100;

        // 放入缓冲区
        pthread_mutex_lock(&mutex);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg)
{
    while(1)
    {    
        // 从缓冲区中取出数据
        pthread_mutex_lock(&mutex);
        int y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutex);

        // 消耗
        printf("Got %d\n", y);
    }
}
```

#### main

```c
int main(int argc, const char *argv[]) {

    srand(time(NULL));
    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (i % 2 == 0)
        {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0)
            {
                perror("pthread_create");
            }
        }
        else
        {
            if (pthread_create(&th[i], NULL, &consumer, NULL)!= 0)
            {
                perror("pthread_create");
            }
        }
        
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL)!= 0)
        {
            perror("pthread_join");
        }
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
```

### 添加判断

```c
void *producer(void *arg)
{
    while(1)
    {
        // 生产
        int x = rand() % 100;

        // 放入缓冲区
        pthread_mutex_lock(&mutex);
        if (count < 10) // 判断缓冲区是否已满
        {
            buffer[count] = x;
            count++;
        }
        else
        {
            printf("Skipped %d\n");
        }
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg)
{
    while(1)
    {    
        int y = -1; // 测试是否越界

        // 从缓冲区中取出数据
        pthread_mutex_lock(&mutex);
        if (count > 0) // 判断缓冲区是否为空
        {
            y = buffer[count - 1];
            count--;
        }
        pthread_mutex_unlock(&mutex);

        // 消耗
        printf("Got %d\n", y);
    }
}
```

### 运行

```zsh
./main
...
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Got 12
Skipped 0
Skipped 0
Got 81
Skipped 0
Skipped 0
Got 71
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Got 31
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Got 57
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
Skipped 0
...
```

可以看到，没有越界，但跳过了很多次，造成资源浪费


## 解决资源浪费

### 使用信号量

设置两个信号量
- 一个缓冲区为空的情况
- 一个缓冲区为满的情况

#### 创建信号量

```c
sem_t empty;
sem_t full;
```

#### main

- 缓冲区为空的情况，初始化为10
- 缓冲区为满的情况，初始化为0

```c
int main(int argc, const char *argv[]) {

    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutex, NULL);

    sem_init(&empty, 0, 10); // 缓冲区为空的情况，初始化为10
    sem_init(&full, 0, 0); // 缓冲区为满的情况，初始化为0

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (i % 2 == 0)
        {
            if (pthread_create(&thread[i], NULL, &producer, NULL) != 0)
            {
                perror("pthread_create");
            }
        }
        else
        {
            if (pthread_create(&thread[i], NULL, &consumer, NULL)!= 0)
            {
                perror("pthread_create");
            }
        }
        
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(thread[i], NULL)!= 0)
        {
            perror("pthread_join");
        }
    }
    
    sem_destroy(&empty);
    sem_destroy(&full);

    pthread_mutex_destroy(&mutex);
    return 0;
}
```

#### 生产者

- 减少empty信号量
- 增加full信号量

```c
void *producer(void *arg)
{
    while(1)
    {
        // 生产
        int x = rand() % 100;

        // 放入缓冲区
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        if (count < 10) // 判断缓冲区是否已满
        {
            buffer[count] = x;
            count++;
        }
        else
        {
            printf("Skipped %d\n");
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
```

#### 消费者

- 减少full信号量
- 增加empty信号量

```c
void *consumer(void *arg)
{
    while(1)
    {    
        int y = -1; // 测试是否越界

        // 从缓冲区中取出数据
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if (count > 0) // 判断缓冲区是否为空
        {
            y = buffer[count - 1];
            count--;
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // 消耗
        printf("Got %d\n", y);
    }
}
```

#### 优化

这里可以不需要判断缓冲区是否为空或已满，因为信号量已经控制了

例如：
- 当`empty`信号量为0时，`full`信号量为10，此时只能运行`consumer`
- 当`full`信号量为0时，`empty`信号量为10，此时只能运行`producer`

所以可以直接将`if`语句去掉

```c
void *producer(void *arg)
{
    while(1)
    {
        // 生产
        int x = rand() % 100;

        // 放入缓冲区
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    while(1)
    {    
        int y = -1; // 测试是否越界

        // 从缓冲区中取出数据
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // 消耗
        printf("Got %d\n", y);
    }
}
```

### 运行

```zsh
./main
...
Got 2
Got 16
Got 70
Got 25
Got 78
Got 10
Got 19
Got 63
Got 35
Got 12
Got 18
Got 92
Got 96
Got 80
...
```

可以看到，没有越界，也没有资源浪费
