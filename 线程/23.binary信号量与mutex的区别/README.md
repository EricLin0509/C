# binary信号量与mutex的区别

## 代码示例

假设现在有两个函数，一个修改全局变量，另一个等待5毫秒

```c
int fuel = 0; // 全局变量

void *routine1(void *arg)
{
    while (1)
    {
        fuel += 10;
        printf("fuel = %d\n", fuel);
    }
}

void *routine2(void *arg)
{
    while (1)
    {
        usleep(5000);
    }
}
```

### 使用binary信号量

```c
#define THREAD_NUM 4

sem_t semFuel;

int fuel = 0; // 全局变量

void *routine1(void *arg)
{
    while (1)
    {
        sem_wait(&semFuel); // 等待信号量
        fuel += 10;
        printf("fuel = %d\n", fuel);
    }
}

void *routine2(void *arg)
{
    while (1)
    {
        sem_post(&semFuel); // 发送信号量
        usleep(5000);
    }
}

int main(int argc, const char * argv[]) {
    pthread_t thread[THREAD_NUM];
    sem_init(&semFuel, 0, 1);
    for (int i = 0; i < THREAD_NUM; i++) {
        if (i % 2 == 0)
        {
            if(pthread_create(thread+i, NULL, &routine1, NULL) != 0)
            {
                perror("pthread_create failed");
                return 1;
            }
        }
        else
        {
            if(pthread_create(thread+i, NULL, &routine2, NULL)!= 0)
            {
                perror("pthread_create failed");
                return 1;
            }
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
}
```

[源代码](binary信号量.c)

#### 运行结果

```bash
gcc -o sem sem.c -pthread
./sem
fuel = 10
fuel = 20
fuel = 30
fuel = 40
fuel = 50
fuel = 60
...
```

可以看到，程序可以一直正常运行，不会出现崩溃的情况

### 使用mutex

```c
#define THREAD_NUM 4

pthread_mutex_t mutexFuel;

int fuel = 0; // 全局变量

void *routine1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutexFuel); // 上锁
        fuel += 10;
        printf("fuel = %d\n", fuel);
    }
}

void *routine2(void *arg)
{
    while (1)
    {
        pthread_mutex_unlock(&mutexFuel); // 解锁
        usleep(5000);
    }
}

int main(int argc, const char * argv[]) {
    pthread_t thread[THREAD_NUM];
    pthread_mutex_init(&mutexFuel, NULL);
    for (int i = 0; i < THREAD_NUM; i++) {
        if (i % 2 == 0)
        {
            if(pthread_create(thread+i, NULL, &routine1, NULL) != 0)
            {
                perror("pthread_create failed");
                return 1;
            }
        }
        else
        {
            if(pthread_create(thread+i, NULL, &routine2, NULL)!= 0)
            {
                perror("pthread_create failed");
                return 1;
            }
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
    pthread_mutex_destroy(&mutexFuel);
}
```

[源代码](mutex.c)

#### 运行结果
```bash
gcc -o mutex mutex.c -pthread
./mutex
./mutex
fuel = 10
fuel = 30
fuel = 20
fuel = 40
fuel = 50
fuel = 60
fuel = 70
fuel = 80
fuel = 90
fuel = 100
fuel = 110
...
fuel = 1970
fuel = 1980
fuel = 1990
fuel = 2000
Fatal glibc error: pthread_mutex_lock.c:94 (___pthread_mutex_lock): assertion failed: mutex->__data.__owner == 0
zsh: IOT instruction (core dumped)  ./mutex
```

可以看到，程序运行一段时间后崩溃，这是因为，在不同线程对mutex加锁或解锁时是未定义的行为，可能会出现死锁的情况

在mutex中，**有个叫作所有权 (Ownership) 的概念，它只允许同个线程对mutex加锁或解锁，否则会出现未定义行为**

## 总结

binary信号量与mutex最大的区别在于，binary信号量没有所有权的概念，而mutex有

binary信号量相比于mutex，更加原始，使用起来更加灵活

