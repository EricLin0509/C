# trylock实用示例

## 代码示例

可以把线程想象成厨师，把共享的数据和mutex想象成炉

## 一个炉的情况

```c
pthread_mutex_t stoveMutex;
int stoveFuel = 100;
```

### 初始化mutex

#### 入口函数部分

```c
pthread_mutex_t stoveMutex;
int stoveFuel = 100;

void *routine(void *arg)
{
    pthread_mutex_lock(&stoveMutex);
    pthread_mutex_unlock(&stoveMutex);
}
```

#### main函数部分

```c
pthread_mutex_t stoveMutex;
int stoveFuel = 100;

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    pthread_t threads[10];
    pthread_mutex_init(&stoveMutex, NULL);
    for (int i = 0; i < 10 ; i++)
    {
        if (pthread_create (&threads[i], NULL, &routine ,NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(threads[i], NULL ) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }

    pthread_mutex_destroy(&stoveMutex);
    return  0 ;
}
```

### 完成入口函数

```c
void *routine(void *arg) {
    pthread_mutex_lock(&stoveMutex);
    int NeededFuel = rand() % 30;
    if (stoveFuel - NeededFuel < 0)
    {
        printf("没有足够的燃料\n");
    }
    else
    {
        stoveFuel -= NeededFuel;
        printf("剩余燃料：%d\n", stoveFuel);
        usleep(500000);
    }
    pthread_mutex_unlock(&stoveMutex);
}
```

### 运行
```bash
gcc -o trylock trylock.c -lpthread
./trylock
剩余燃料：91
剩余燃料：74
剩余燃料：50
剩余燃料：23
剩余燃料：14
剩余燃料：11
没有足够的燃料
没有足够的燃料
没有足够的燃料
没有足够的燃料
```

## 假设现在有4个炉

```c
pthread_mutex_t stoveMutexes[4];
int stoveFuel[4] = {100, 100, 100, 100};
```

### 代码

#### 入口函数部分

```c
pthread_mutex_t stoveMutexes[4];
int stoveFuel[4] = {100, 100, 100, 100};

void *routine(void *arg) {
    pthread_mutex_lock(&stoveMutex);
    int NeededFuel = rand() % 30;
    if (stoveFuel - NeededFuel < 0)
    {
        printf("没有足够的燃料\n");
    }
    else
    {
        stoveFuel -= NeededFuel;
        printf("剩余燃料：%d\n", stoveFuel);
        usleep(500000);
    }
    pthread_mutex_unlock(&stoveMutex);
}
```

#### main函数部分

```c
pthread_mutex_t stoveMutexes[4];
int stoveFuel[4] = {100, 100, 100, 100};

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    pthread_t threads[10];
    for (int i = 0; i < 4; i++)
    {
        pthread_mutex_init(&stoveMutexes[i], NULL);
    }
    for (int i = 0; i < 10 ; i++)
    {
        if (pthread_create (&threads[i], NULL, &routine ,NULL) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(threads[i], NULL ) != 0)
        {
            perror("pthread_join");
            return 2;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_mutex_destroy(&stoveMutexes[i]);
    }
    return  0 ;
}
```

### 这里出现的问题

如果把`routine`函数中的`stoveFuel`改成`stoveFuel[0]`，那只能调用第一个“炉”的燃料，

如果传递数组下标到`routine`函数，虽说可以调用不同的“炉”，但是会生硬，无法让“厨师”们自己去寻找合适的炉

## 解决方案——trylock

### 遍历所有炉

```c
void *routine(void *arg)
{
    for (int i = 0; i < 4; i++) {   }
}
```

### 尝试找合适的炉

```c
void *routine(void *arg)
{
    for (int i = 0; i < 4; i++)
    {
        if (pthread_mutex_trylock(&stoveMutexes[i]) == 0) {   }
    }
}
```

### 使用合适的炉

```c
void *routine(void *arg)
{
    for (int i = 0; i < 4; i++)
    {
        if (pthread_mutex_trylock(&stoveMutexes[i]) == 0)
        {
            int NeededFuel = rand() % 30;
            if (stoveFuel[i] - NeededFuel < 0)
            {
                printf("没有足够的燃料\n");   
            }
            else
            {
                stoveFuel[i] -= NeededFuel;
                printf("剩余燃料：%d\n", stoveFuel[i]);
                usleep(500000);
            }
        }
    }
}
```

### 运行
```bash
gcc -o trylock trylock.c -pthread
./trylock
剩余燃料：91
剩余燃料：74
剩余燃料：50
剩余燃料：23
```

### 原因

当第五个“厨师”来的时候，发现所有的“炉”都被占用了，就会直接跳过，不会等待

### 解决方案——重试

```c
void *routine(void *arg)
{
    for (int i = 0; i < 4; i++)
    {
        if (pthread_mutex_trylock(&stoveMutexes[i]) == 0)
        {
            int NeededFuel = rand() % 30;
            if (stoveFuel[i] - NeededFuel < 0)
            {
                printf("没有足够的燃料\n");   
            }
            else
            {
                stoveFuel[i] -= NeededFuel;
                usleep(500000);
                printf("剩余燃料：%d\n", stoveFuel[i]);
            }
        }
        else
        {
            if (i == 3) // 如果最后一个“炉”也被占用了，就从头开始
            {
                usleep(300000);
                i = 0;
            }
        }
    }
}
```

[源代码](trylock实用示例.c)

### 运行
```bash
gcc -o trylock trylock.c -pthread
./trylock
剩余燃料：81
剩余燃料：83
剩余燃料：87
剩余燃料：83
剩余燃料：73
剩余燃料：81
剩余燃料：76
剩余燃料：60
剩余燃料：62
剩余燃料：58
```

## 总结

当你有**多个共享数据，并且不需要指定某个线程去操作某个数据**的时候，就可以使用`trylock`，这样可以实现线程并行