# 应用示例 (计算整个数组的和)

## 代码

### 初始化线程

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

pthread_t thread[2];
```

### 创建线程

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

pthread_t thread[2];

for (int i = 0; i < 2; i++)
{
    if (pthread_create(&thread[i], NULL, thread_func, NULL) != 0)
    {
        perror("pthread_create");
        return 1;
    }
}
```

### 传递参数

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

pthread_t thread[2];

for (int i = 0; i < 2; i++)
{
    int *pass = malloc(sizeof(int));
    *pass = i * 5;

    if (pthread_create(&thread[i], NULL, &routine, pass) != 0)
    {
        perror("pthread_create");
        return 1;
    }
}
```

### 入口函数

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *args)
{
    int *index = (int *)args;
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += index[i];
    }
}
```

### 返回值

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *args)
{
    int *index = (int *)args;
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += index[i];
    }
    *(int *)args = sum;
    return args;
}
```

### 获取返回值

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

pthread_t thread[2];

for (int i = 0; i < 2; i++)
{
    int *pass = malloc(sizeof(int));
    *pass = i * 5;

    if (pthread_create(&thread[i], NULL, &routine, pass) != 0)
    {
        perror("pthread_create");
        return 1;
    }
}

for (int i = 0; i < 2; i++)
{
    int *result;
    if (pthread_join(thread[i], &result) != 0)
    {
        perror("pthread_join");
        return 2;
    }
}
```

### 计算结果

```c
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

pthread_t thread[2];

for (int i = 0; i < 2; i++)
{
    int *pass = malloc(sizeof(int));
    *pass = i * 5;

    if (pthread_create(&thread[i], NULL, &routine, pass) != 0)
    {
        perror("pthread_create");
        return 1;
    }
}

int global_sum = 0;

for (int i = 0; i < 2; i++)
{
    int *result;
    if (pthread_join(thread[i], &result) != 0)
    {
        perror("pthread_join");
        return 2;
    }
    global_sum += *result;
    free(result);
}
```
[源代码](线程应用示例.c)